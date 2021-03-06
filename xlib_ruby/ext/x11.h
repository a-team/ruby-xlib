#ifndef X11_RUBY_H
#define X11_RUBY_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/Xutil.h>
#include <locale.h>

enum { WMProtocols, WMDelete, WMName, WMState, WMLast };/* default atoms */
enum { NetSupported, NetWMName, NetLast };      /* EWMH atoms */

typedef struct Client_t Client;
typedef struct WM_t WM;

struct Client_t {
    char name[256];
    char class[256];
    int x,y,w,h;
    int rx,ry,rw,rh; //revert geo
    int basew,baseh,incw,inch,maxw,maxh,minw,minh;
    int minax,maxax,minay,maxay;
    long flags;
    unsigned int border, oldborder;
    Bool isbanned, isfixed, ismax, isfloating, wasfloating;
    WM *manager;
    Window win;
};

typedef struct Key_t {
    unsigned long mod;
    KeySym keysym;
    const char *arg;
    void (*func)(const char *arg);
} Key;

struct WM_t {
    int screen, sx, sy, sw, sh, wax, way, waw, wah;
    Client *selected;
    Client* order;
    Display *dpy;
    Window root;
    Bool running; 
    Bool otherwm;
    Bool manage_override_redirect_windows;
    int (*xerrorxlib)(Display *, XErrorEvent *);
    Atom wmatom[WMLast];
    Atom netatom[NetLast];
    unsigned int clients_num;
    Client* clients;
};

int manageable_p(WM* wm, Window w);
void init_client(WM* wm, Window w, Client* c);
void manage_client(WM* wm, XWindowAttributes *wa, Client* c);
void resize(WM* winman, Client *c, int x, int y, int w, int h, int sizehints);
Client* query_clients(WM* winman);
void raise_client(Client* c);
void ban_client(Client* c);
void unban_client(Client* c);
void unborder_client(Client* c);
void border_client(Client* c, int w);
WM* Init_WM();
int event_pending(WM* winman);
int event_next_source(WM* winman);
char* event_next_type(WM* winman);
void event_pop(WM* winman);
void Destroy_WM(WM* winman);
Client* client_ftw(WM* wm, Window w);

#endif
