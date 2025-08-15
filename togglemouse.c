static Window fw = 0;
static int locked = 0;

void
togglemouse(const Arg *arg) {
    if (locked) {
        XUngrabPointer(dpy, CurrentTime);
		XWarpPointer(dpy, None, selmon->sel->win, 0, 0, 0, 0, selmon->sel->w/2, selmon->sel->h/2);
        if (fw) {
            XDestroyWindow(dpy, fw);
            fw = 0;
        }
        locked = 0;
        return;
    }

    Window root = RootWindow(dpy, screen);

    XSetWindowAttributes attrs;
    attrs.override_redirect = True;
    attrs.event_mask = 0;

    fw = XCreateWindow(
        dpy, root, 0, sh - 1, 1, 1, 0,
        DefaultDepth(dpy, screen),
        InputOutput, DefaultVisual(dpy, screen),
        CWOverrideRedirect | CWEventMask, &attrs
    );

    XMapRaised(dpy, fw);
    XSync(dpy, False);

    XWarpPointer(dpy, None, root, 0, 0, 0, 0, 0, sh - 1);

    if (XGrabPointer(dpy, fw, True,
                     0,
                     GrabModeAsync,
                     GrabModeAsync,
                     fw,
                     None,
                     CurrentTime) != GrabSuccess) {
        XDestroyWindow(dpy, fw);
        fw = 0;
        return;
    }

    locked = 1;
}
