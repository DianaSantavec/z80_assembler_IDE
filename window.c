#include <libraries.h>

int main(int argc, char *argv[]) {
  GtkWidget *window, *menu, *main_vbox;

  gtk_init(&argc, &argv);
  *window = create_window();
  gtk_signal_connect (GTK_OBJECT(window), "destroy", GTK_SIGNAL_FUNC(gtk_main_quit),"WM destroy");
  main_vbox = gtk_vbox_new(FALSE, 1);
  gtk_container_border_width (GTK_CONTAINER (main_vbox), 1);
  gtk_container_add (GTK_CONTAINER (window), main_vbox);
  gtk_widget_show (main_vbox);
  get_menu (window, &menu);
  gtk_box_pack_start (GTK_BOX (main_vbox), menu, FALSE, TRUE, 0);
  gtk_widget_show (menu);

  gtk_widget_show(window);
  gtk_main();

  return 0;
}