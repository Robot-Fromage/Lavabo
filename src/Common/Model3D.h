/*************************************************************************
*
*   Lavabo
*__________________
*
* Model3D.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


#include <GL/glew.h>


#include <vector>
#include <string>
#include <glm/vec3.hpp>


class  cModel3D
{
    
public:
    // Construction / Destruction
    ~cModel3D();
    cModel3D( std::string iObjPath );

public:
    // Public Interface
    void Load();
    void  Render()  const;
    GLuint GetVBO_ID() const;

private:
    GLuint  mVBO_ID;
    std::vector<glm::vec3> mObjectVertices;
    std::vector<glm::vec3> mObjectNormals;
    int mBufferHalfSize;
    int mTriangleCount;
    std::string mModelSource;
};

