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
GtkWidget *vertical_container_box_text;
GtkWidget *text_view; 
GtkTextBuffer *text_buffer;
//GtkWidget *grid;


GtkActionGroup *action_group;

GtkBox *widget_box;
//menu items
/*
GtkWidget *file_list;
GtkWidget *edit_list;
GtkWidget *help_list;

GtkWidget *file_menu;
GtkWidget *edit_menu;
GtkWidget *help_menu;

GtkWidget *new_item;
GtkWidget *save_item;
GtkWidget *open_item;
GtkWidget *quit_item;
GtkWidget *copy_item;
GtkWidget *cut_item;
GtkWidget *paste_item;
GtkWidget *help_item;*/

void on_open_file(){
    printf("hello world");
}

void create_window(){
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 800); 
  gtk_window_set_title(GTK_WINDOW(window),"Z80 assembler IDE");
  g_signal_connect (window, "destroy", G_CALLBACK(destroy), NULL);
  
 // grid = gtk_grid_new();

  create_menubar();

  create_textbox_filed();

  //gtk_box_pack_start(GTK_BOX(widget_box),vertical_container_box,0,0,1);
  //gtk_box_pack_start(GTK_BOX(widget_box),vertical_container_box_text,0,0,1);
  
  //gtk_widget_show (menu_bar);
  gtk_widget_show (text_view);
  //gtk_widget_show(window);
}

void create_menubar(){  
    vertical_container_box = gtk_vbox_new (FALSE , 5);
    gtk_container_border_width (GTK_CONTAINER (vertical_container_box), 1);
    //gtk_container_add (GTK_CONTAINER(window), vertical_container_box);
    //gtk_widget_show (vertical_container_box);
  
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

/*void create_menubar(){
   /* vertical_container_box = gtk_vbox_new(FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), vertical_container_box);
    menu_bar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(vertical_container_box), menu_bar, FALSE, TRUE, 5);

    file_list = gtk_menu_item_new_with_label("File");
    edit_list = gtk_menu_item_new_with_label("Edit");
    help_list = gtk_menu_item_new_with_label("Help");

    gtk_menu_shell_append(GTK_MENU_SHELL (menu_bar), file_list);
    gtk_menu_shell_append(GTK_MENU_SHELL (menu_bar), edit_list);
    gtk_menu_shell_append(GTK_MENU_SHELL (menu_bar), help_list);

    file_menu = gtk_menu_new();
    edit_menu = gtk_menu_new();
    help_menu = gtk_menu_new();

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_list), file_menu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(edit_list), edit_menu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_list), help_menu);

    new_item = gtk_menu_item_new_with_label ("New");
    save_item = gtk_menu_item_new_with_label ("Save");
    open_item = gtk_menu_item_new_with_label ("Open");
    quit_item = gtk_menu_item_new_with_label ("Quit");
    copy_item = gtk_menu_item_new_with_label ("Copy");
    cut_item = gtk_menu_item_new_with_label ("Cut");
    paste_item = gtk_menu_item_new_with_label ("Paste");
    help_item = gtk_menu_item_new_with_label ("Help");

    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu),new_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu),save_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu),open_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu),quit_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu),copy_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu),cut_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu),paste_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu),help_item);

    *//*

    static const GtkActionEntry file_entries[] = {
        {"FileMenu", NULL, "_File"},
        {"Open", GTK_STOCK_OPEN, "_Open","<control>O","Open a file", G_CALLBACK(on_open_file)},
    };

    action_group = gtk_action_group_new("Common_Actions");
    gtk_action_group_add_action(action_group,file_entries,G_N_ELEMENTS (file_entries),(gpointer)(&appState));

}*/

void create_textbox_filed(){
    vertical_container_box_text = gtk_vbox_new(FALSE,2);
    //gtk_container_add(GTK_CONTAINER(window),vertical_container_box_text);

    text_view = gtk_text_view_new();
    gtk_box_pack_start (GTK_BOX (vertical_container_box), text_view, 1, 1, 0);

    text_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text (text_buffer, ";Z80 assembly",-1);
}