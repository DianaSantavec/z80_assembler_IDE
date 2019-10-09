#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

void hello_world(GtkWidget *window, gpointer data){
    g_message ("hello world!\n");
}

void destroy(GtkWidget *widget, gpointer data){
    gtk_main_quit();
}

static GtkItemFactoryEntry menu_items[] = {
    { "/_File",         NULL,         NULL,          0, "<Branch>"     },
    { "/File/_New",     "<control>N", hello_world,   0, NULL           },
    { "/File/_Open",    "<control>O", hello_world,   0, NULL           },
    { "/File/_Save",    "<control>S", hello_world,   0, NULL           },
    { "/File/Quit",     "<control>Q", gtk_main_quit, 0, NULL           },
    { "/_Edit",         NULL,         NULL,          0, "<Branch>"     },
    { "/Edit/copy",     "<control>C", hello_world,   0, NULL           },
    { "/Edit/cut",      "<control>X", hello_world,   0, NULL           },
    { "/Edit/paste",    "<control>V", hello_world,   0, NULL           },
    { "/_Help",         NULL,         NULL,          0, "<LastBranch>" },
    { "/_Help/About",   "<control>H", hello_world,   0, NULL           },
};
GtkWidget *window;
GtkWidget *vertikal_container_box;
GtkWidget *menubar;

void create_window(){
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 800); 
  gtk_signal_connect (window, "destroy", G_CALLBACK(destroy), NULL);
  
  create_menubar();
  
  gtk_widget_show (menubar);
  gtk_widget_show(window);
}

void create_menubar(){
  vertikal_container_box = gtk_vbox_new (FALSE , 5);
  gtk_container_border_width (GTK_CONTAINER (vertikal_container_box), 1);
  gtk_container_add (GTK_CONTAINER(window), vertikal_container_box);
  gtk_widget_show (vertikal_container_box);
  
  create_menu (window, &menubar);
  gtk_box_pack_start (GTK_BOX (vertikal_container_box), menubar, FALSE, TRUE, 5);
}

void create_menu ( GtkWidget  *window, GtkWidget **menubar ){
  GtkItemFactory *item_factory;
  GtkAccelGroup *keyboard_accelerators;
  gint nmenu_items = sizeof (menu_items) / sizeof (menu_items[0]);

  keyboard_accelerators = gtk_accel_group_new ();

  item_factory = gtk_item_factory_new (GTK_TYPE_MENU_BAR, "<main>", keyboard_accelerators);
  gtk_item_factory_create_items (item_factory, nmenu_items, menu_items, NULL);
  gtk_window_add_accel_group (GTK_WINDOW (window), keyboard_accelerators);

  if (menubar){
    *menubar = gtk_item_factory_get_widget (item_factory, "<main>");
  }
}
