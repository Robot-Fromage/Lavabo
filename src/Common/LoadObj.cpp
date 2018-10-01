/*************************************************************************
*
*   Lavabo
*__________________
*
* LoadObj.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "LoadObj.h"


#include <sstream>
#include <fstream>
#include <iostream>


#include <glm/geometric.hpp>


using namespace std;


void load_obj(const char* filename, vector<glm::vec3> &vertices, vector<glm::vec3> &normals, vector< int64_t > &elements)
{
    ifstream in(filename, ios::in);
    if (!in)
    {
        cerr << "Cannot open " << filename << endl; exit(1);
    }

    string line;
    while (getline(in, line))
    {
        if (line.substr(0,2) == "v ")
        {
            istringstream s(line.substr(2));
            glm::vec3 v;
            s >> v.x;
            s >> v.y;
            s >> v.z;
            vertices.push_back(v);
        }
        else if (line.substr(0,2) == "f ")
        {
            istringstream s(line.substr(2));
            int64_t a,b,c;
            s >> a; s >> b; s >> c;
            a--; b--; c--;
           elements.push_back(a); elements.push_back(b); elements.push_back(c);
        }
        else if (line[0] == '#')
        {
            /* ignoring this line */
        }
        else
        {
            /* ignoring this line */
        }
    }

    normals.resize(vertices.size(), glm::vec3(0.0, 0.0, 0.0));
    for (int i = 0; i < elements.size(); i+=3)
    {
        int64_t ia = elements[i];
        int64_t ib = elements[i+1];
        int64_t ic = elements[i+2];

        glm::vec3 normal = glm::normalize(glm::cross(
        glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
        glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));
        normals[ia] = normals[ib] = normals[ic] = normal;
    }
}

