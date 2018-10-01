/*************************************************************************
*
*   Lavabo
*__________________
*
* LoadObj.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


#include <GL/glew.h>


#include <vector>
#include <inttypes.h>


#include <glm/vec3.hpp>


void load_obj(const char* filename, std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector< int64_t > &elements);

