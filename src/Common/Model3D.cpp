/*************************************************************************
*
*   Lavabo
*__________________
*
* Model3D.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "Model3D.h"


#include "LoadObj.h"


#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cModel3D::~cModel3D()
{
    if( glIsBuffer( mVBO_ID ) == GL_TRUE )
        glDeleteBuffers(1, &mVBO_ID );
}


cModel3D::cModel3D( std::string iObjPath ) :
    mVBO_ID( 0 ),
    mObjectVertices( std::vector<glm::vec3>() ),
    mObjectNormals( std::vector<glm::vec3>() ),
    mBufferHalfSize( 0 ),
    mTriangleCount( 0 ),
    mModelSource( iObjPath )
{
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------- Public Interface


void
cModel3D::Load()
{
    // Destruction before rebuild
    if( glIsBuffer( mVBO_ID ) == GL_TRUE )
        glDeleteBuffers(1, &mVBO_ID );

    std::vector<int64_t> obj_elements;
    std::vector<glm::vec3> obj_vertices;
    std::vector<glm::vec3> obj_normals;
    load_obj( mModelSource.c_str(), obj_vertices, obj_normals, obj_elements);

    mObjectVertices.clear();
    mObjectNormals.clear();

    mObjectVertices.reserve( obj_elements.size() );
    mObjectNormals.reserve( obj_elements.size() );

    for( int i = 0; i < obj_elements.size(); ++i )
    {
        mObjectVertices.push_back( obj_vertices[ obj_elements[i] ] );
        mObjectNormals.push_back( obj_normals[ obj_elements[i] ] );
    }

    mTriangleCount = obj_elements.size();
    mBufferHalfSize = mTriangleCount * sizeof(glm::vec3);

    glGenBuffers( 1, &mVBO_ID );

    glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID );

    glBufferData(GL_ARRAY_BUFFER, mBufferHalfSize * 2, NULL, GL_STATIC_DRAW);
        glBufferSubData( GL_ARRAY_BUFFER, 0, mBufferHalfSize, &mObjectVertices[0] );
        glBufferSubData( GL_ARRAY_BUFFER, mBufferHalfSize, mBufferHalfSize, &mObjectNormals[0] );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}


void
cModel3D::Render() const
{
    glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET( 0 ) );
    glEnableVertexAttribArray( 0 );

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET( mBufferHalfSize ) );
    glEnableVertexAttribArray( 1 );

    glDrawArrays( GL_TRIANGLES, 0, mTriangleCount );

    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}


GLuint
cModel3D::GetVBO_ID() const
{
    return  mVBO_ID;
}

