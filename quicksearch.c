void
quicksearch(const Arg *arg)
{
	Client *c;
	Monitor *m;
	char *names = NULL;
	size_t names_size = 0;
	size_t names_len = 0;
	int client_count = 0;
	Client **clients = NULL;
	size_t clients_size = 0;
	
	for (m = mons; m; m = m->next) {
		for (c = m->clients; c; c = c->next) {
			if (!ISVISIBLE(c)) {
				client_count++;
				
				char tag_str[64] = "[";
				int tag_len = 1;
				int first = 1;
				for (int i = 0; i < LENGTH(tags); i++) {
					if (c->tags & (1 << i)) {
                        
						if (!first) tag_len += snprintf(tag_str + tag_len, sizeof(tag_str) - tag_len, ",");
						tag_len += snprintf(tag_str + tag_len, sizeof(tag_str) - tag_len, "%d", i + 1);
						first = 0;
					}
				}
				tag_len += snprintf(tag_str + tag_len, sizeof(tag_str) - tag_len, "] ");
				
				size_t name_len = strlen(c->name);
				size_t needed = names_len + tag_len + name_len + 1;
				
				if (needed > names_size) {
					names_size = needed * 2;
					names = realloc(names, names_size);
					if (!names)
						die("quicksearch: realloc failed");
				}
				
				if (client_count > clients_size) {
					clients_size = client_count * 2;
					clients = realloc(clients, clients_size * sizeof(Client *));
					if (!clients)
						die("quicksearch: realloc failed");
				}
				
                    strlcpy(names + names_len, tag_str, names_size - names_len);
                    names_len += tag_len;
                    strlcpy(names + names_len, c->name, names_size - names_len);

				names_len += name_len;
				names[names_len] = '\n';
				names_len++;
				
				clients[client_count - 1] = c;
			}
		}
	}
	
	if (client_count == 0)
		return;
	
	names[names_len - 1] = '\0';
	
	char dmenu_cmd[256];
	snprintf(dmenu_cmd, sizeof(dmenu_cmd), "echo '%s' | dmenu -l 10 -i -p 'Switch to client:'", names);
	
	FILE *fp = popen(dmenu_cmd, "r");
	if (!fp) {
		free(names);
		free(clients);
		return;
	}
	
	char selected_name[256];
	if (fgets(selected_name, sizeof(selected_name), fp) != NULL) {
		size_t len = strlen(selected_name);
		if (len > 0 && selected_name[len - 1] == '\n')
			selected_name[len - 1] = '\0';
		
		char *client_name = strchr(selected_name, ']');
		if (client_name) {
			client_name += 2;
			
			for (int i = 0; i < client_count; i++) {
				if (strcmp(clients[i]->name, client_name) == 0) {
					Client *selected_client = clients[i];
					
					if (selected_client->mon != selmon)
						selmon = selected_client->mon;
					
					Arg view_arg;
					view_arg.ui = selected_client->tags;
					view(&view_arg);

					focus(selected_client);

                    if (selected_client != nexttiled(selmon->clients)) {
                        zoom(0);
                    }
					
					break;
				}
			}
		}
	}
	
	pclose(fp);
	free(names);
	free(clients);
}
