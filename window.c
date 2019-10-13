#include <libraries.h>

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  create_window();

  gtk_container_add(GTK_CONTAINER(window),vertical_container_box);

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}