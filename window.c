#include <libraries.h>

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  create_window();
  gtk_main();

  return 0;
}