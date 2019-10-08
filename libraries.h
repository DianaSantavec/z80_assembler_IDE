#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

void hello_world(GtkWidget *window, gpointer data){
    g_message ("hello world!\n");
}

GtkWidget create_window(){
    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//    gtk_widget_show(window);
    g_signal_connect(window, "destroy",
    G_CALLBACK(gtk_main_quit), NULL);  

    return *window;
}

    static GtkItemFactoryEntry menu_items[] = {
        { "/_File",         NULL,         NULL, 0, "<Branch>" },
        { "/File/_New",     "<control>N", hello_world, 0, NULL },
        { "/File/_Open",    "<control>O", hello_world, 0, NULL },
        { "/File/_Save",    "<control>S", hello_world, 0, NULL },
        { "/File/Quit",     "<control>Q", gtk_main_quit, 0, NULL },
        { "/_Edit",         NULL,         NULL, 0, "<Branch>" },
        { "/Edit/copy",     "<control>C", hello_world, 0, NULL },
        { "/Edit/cut",      "<control>X", hello_world, 0, NULL },
        { "/Edit/paste",    "<control>V", hello_world, 0, NULL },
        { "/_Help",         NULL,         NULL, 0, "<LastBranch>" },
        { "/_Help/About",   NULL,         NULL, 0, NULL },
    };

void get_menu( GtkWidget  *window, GtkWidget **menubar ){
  GtkItemFactory *item_factory;
  GtkAccelGroup *accel_group;
  gint nmenu_items = sizeof (menu_items) / sizeof (menu_items[0]);

  accel_group = gtk_accel_group_new ();

  item_factory = gtk_item_factory_new (GTK_TYPE_MENU_BAR, "<main>", 
                                       accel_group);
  gtk_item_factory_create_items (item_factory, nmenu_items, menu_items, NULL);
  gtk_window_add_accel_group (GTK_WINDOW (window), accel_group);

  if (menubar)
    *menubar = gtk_item_factory_get_widget (item_factory, "<main>");
}
