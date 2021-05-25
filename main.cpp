#include <iostream>

#include "src/spyder.h"

int main() {
  spyder::Spyder s;
  s.GameLoop();
  s.End();

  return 0;
}
