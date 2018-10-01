/*************************************************************************
*
*   Lavabo
*__________________
*
* ViewDisplay3D.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "ViewDisplay3D.h"


#include "Model3D.h"
#include "Shader3D.h"


#include <QTimer>


#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cViewDisplay3D::~cViewDisplay3D()
{
    Destroy();
}


cViewDisplay3D::cViewDisplay3D( QWidget*  parent ) :
    tSuperClass( parent ),
    mModel3D( NULL ),
    mShader3D( NULL )
    //mTimer( NULL )
{
    Init();
    Build();
    Compose();
}


//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------- Public View API


void
cViewDisplay3D::SetModel3D( cModel3D* iModel )
{
    if( mModel3D )
    {
        delete  mModel3D;
        mModel3D = 0;
    }

    mModel3D = iModel;
}


cModel3D*
cViewDisplay3D::Model3D()  const
{
    return  mModel3D;
}


void
cViewDisplay3D::SetShader3D( cShader3D* iShader )
{
    if( mShader3D )
    {
        delete  mShader3D;
        mShader3D = 0;
    }

    mShader3D = iShader;
}


cShader3D*
cViewDisplay3D::Shader3D()  const
{
    return  mShader3D;
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Event


void
cViewDisplay3D::resizeEvent( QResizeEvent* event )
{
    tSuperClass::resizeEvent( event );
    Compose();
}


//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------- GL


void
cViewDisplay3D::initializeGL()
{
    glewInit();

    if( mModel3D ) mModel3D->Load();
    if( mShader3D ) mShader3D->Load();

    glClearColor( 0.8, 0.8, 0.8, 1.0 );
    glEnable(GL_DEPTH_TEST);

    mViewMatrix = glm::lookAt( glm::vec3( 2.5, 2.5, 4 ), glm::vec3( 0, 1, 0 ), glm::vec3( 0, 1, 0 ) );
    mModelMatrix = glm::mat4(1.0);
}

void
cViewDisplay3D::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);

    mProjectionMatrix = glm::perspective( 45.0, (double) w/h, 1.0, 100.0);
}


void
cViewDisplay3D::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mModelMatrix = glm::rotate( mModelMatrix, 0.01f, glm::vec3( 0, 1, 0 ) );

    glm::mat4 modelview = mViewMatrix * mModelMatrix;
    mNormalMatrix = glm::inverse( glm::transpose( glm::mat3( modelview ) ) );

    GLuint shader_id = 0;
    if( mShader3D )
        shader_id = mShader3D->GetProgramID();

    if( shader_id )
    {
        glUseProgram( shader_id );
        glUniformMatrix4fv( glGetUniformLocation( shader_id, "projection" ), 1, GL_FALSE, glm::value_ptr( mProjectionMatrix ) );
        glUniformMatrix4fv( glGetUniformLocation( shader_id, "view" ), 1, GL_FALSE, glm::value_ptr( mViewMatrix ) );
        glUniformMatrix4fv( glGetUniformLocation( shader_id, "model" ), 1, GL_FALSE, glm::value_ptr( mModelMatrix ) );
        glUniformMatrix3fv( glGetUniformLocation( shader_id, "normalMatrix" ), 1, GL_FALSE, glm::value_ptr( mNormalMatrix ) );
    }

    if( mModel3D )
        mModel3D->Render();

    glUseProgram( 0 );

    emit  PaintCompleted();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
cViewDisplay3D::Init()
{
    //mTimer = new QTimer;
}


void
cViewDisplay3D::Build()
{
    //mTimer->setInterval( 1000.0 / 60.0 );
    //QObject::connect( mTimer, SIGNAL( timeout() ), this, SLOT( update() ) );
    //mTimer->start();
}


void
cViewDisplay3D::Compose()
{
    // Nothing ATM
}


void
cViewDisplay3D::Destroy()
{
    delete  mModel3D;
    delete  mShader3D;
}

