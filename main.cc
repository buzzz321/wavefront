#include "wavefrontreader.h"
#include <iostream>

int main() {
  WaveFrontReader wf("../plane.obj");

  Mesh obj;
  wf.readVertices(obj);
  std::cout << " hej " << std::endl;
  return 0;
}
