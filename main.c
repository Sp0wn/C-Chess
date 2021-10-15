#include "Menu/ui.h"
#include "Menu/input.h"

#include <stdio.h>

int main()
{
  show_logo();
  show_main_menu_en();
  int a = input_menu();
  return 0;
}
