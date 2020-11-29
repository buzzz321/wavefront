#include <iostream>
#include "wavefrontreader.h"

int main(){
    WaveFrontReader wf("../kub.obj");

    Mesh obj;
    wf.readVertices(obj);
    std::cout<< " hej "<< std::endl;
    return 0;
}
    
