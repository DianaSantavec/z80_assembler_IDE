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
GtkWidget *vertical_container_box;
GtkWidget *menu_bar;
GtkWidget *text_view; 
GtkTextBuffer *text_buffer;


GtkActionGroup *action_group;

GtkBox *widget_box;

void on_open_file(){
    printf("hello world");
}

void create_window(){
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 800); 
  gtk_window_set_title(GTK_WINDOW(window),"Z80 assembler IDE");
  g_signal_connect (window, "destroy", G_CALLBACK(destroy), NULL);

  create_menubar();

  create_textbox_filed();
}

void create_menubar(){  
    vertical_container_box = gtk_vbox_new (FALSE , 5);
    gtk_container_border_width (GTK_CONTAINER (vertical_container_box), 1);
  
    create_menu (window, &menu_bar);
    gtk_box_pack_start (GTK_BOX (vertical_container_box), menu_bar, FALSE, TRUE, 5);
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

void create_textbox_filed(){

    text_view = gtk_text_view_new();
    gtk_box_pack_start (GTK_BOX (vertical_container_box), text_view, 1, 1, 0);

    text_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text (text_buffer, ";Z80 assembly",-1);
}