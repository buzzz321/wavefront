#include "wavefrontreader.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

WaveFrontReader::WaveFrontReader(std::string filename) : m_filename(filename) {}

void WaveFrontReader::readVertices(Mesh& obj) {
    std::ifstream myfile(m_filename);
    std::string line;
    uint32_t debug_index{0};
    uint32_t vector_order{
        0}; // we use this to error out if order is changed in .obj file
    uint32_t vector_index{0};
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            auto vpos = line.find("v ");
            if (vpos == 0) {
                vector_order = 1;
                std::stringstream conv{line.substr(1)};
                float x, y, z;
                conv >> x >> y >> z;
                std::cout << "v x " << x << " y " << y << " z " << z
                          << std::endl;
                Vertex vert;
                vert.Coord = glm::vec3(x, y, z);
                obj.vertices.push_back(vert);
                continue;
            }
            vpos = line.find("vt ");
            if (vpos == 0) {
                if (vector_order == 1) {
                    vector_index = 0;
                }
                vector_order = 2;

                std::stringstream conv{line.substr(2)};
                float x, y;
                conv >> x >> y;
                std::cout << "vt x " << x << " y " << y << std::endl;
                obj.vertices[vector_index].TextureCoord = glm::vec2(x, y);
                vector_index++;
                continue;
            }
            vpos = line.find("vn ");
            if (vpos == 0) {
                if (vector_order == 2) {
                    vector_index = 0;
                }
                vector_order = 3;

                std::stringstream conv{line.substr(2)};
                float x, y, z;
                conv >> x >> y >> z;
                std::cout << "vn x " << x << " y " << y << std::endl;
                obj.vertices[vector_index].Normal = glm::vec3(x, y, z);
                vector_index++;
                continue;
            }
            vpos = line.find("f ");
            if (vpos == 0) {
                // f 1/2/3 1/2/3 13/1/2
                // f 11/108/34 13/109/34 7/106/34
                std::istringstream splitter{line.substr(2)};
                std::cout << line << std::endl;
                std::string face;
                std::string face_index;
                uint64_t index;
                while (std::getline(splitter, face, ' ')) {
                    std::cout << face << std::endl;
                    auto start_pos = face.find('/');
                    index = std::stoul(face.substr(0, start_pos), nullptr);
                    obj.indicies.push_back(index - 1);
                    // std::cout << "start_pos" << start_pos << std::endl;
                    auto end_pos = face.find('/', start_pos + 1);
                    // std::cout << "end_pos" << end_pos << std::endl;
                    if (start_pos != end_pos - 1) {
                        index =
                            std::stoul(face.substr(start_pos + 1,
                                                   end_pos - (start_pos + 1)),
                                       nullptr);
                        obj.texture_indicies.push_back(index - 1);
                    }
                    if (start_pos != end_pos - 1) {
                        index = std::stoul(face.substr(end_pos + 1), nullptr);
                        obj.normal_indicies.push_back(index - 1);
                    }
                    std::cout << "f " << obj.indicies.back() + 1 << "/"
                              << obj.texture_indicies.back() + 1 << "/"
                              << obj.normal_indicies.back() + 1 << std::endl;
                }
            }
        }
        obj.indicies.shrink_to_fit();
        obj.vertices.shrink_to_fit();
        myfile.close();
    } else
        std::cout << "Unable to open file";
}
