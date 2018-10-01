/*************************************************************************
*
*   Lavabo
*__________________
*
* Program.ViewDisplay3D.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "Program.ViewDisplay3D.h"


#include <GL/glew.h>


#include "ViewDisplay3D.h"
#include "Model3D.h"
#include "Shader3D.h"


namespace nProgram {
namespace nViewDisplay3D {


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cProgram_ViewDisplay3D::~cProgram_ViewDisplay3D()
{
    Destroy();
}


cProgram_ViewDisplay3D::cProgram_ViewDisplay3D( QWidget*  parent ) :
    tSuperClass( parent ),
    mViewDisplay3D( NULL ),
    mModel3D( NULL ),
    mShader3D( NULL )
{
    Init();
    Build();
    Compose();
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Event


void
cProgram_ViewDisplay3D::resizeEvent( QResizeEvent* event )
{
    tSuperClass::resizeEvent( event );
    Compose();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
cProgram_ViewDisplay3D::Init()
{
    mViewDisplay3D = new cViewDisplay3D( this );

    mModel3D = new cModel3D( "resources/obj3d/armadillo.obj");
    mShader3D = new cShader3D( "resources/shaders/ViewDisplay3D.vert", "resources/shaders/ViewDisplay3D.frag" );
}


void
cProgram_ViewDisplay3D::Build()
{
    mViewDisplay3D->SetModel3D( mModel3D );
    mViewDisplay3D->SetShader3D( mShader3D );
}


void
cProgram_ViewDisplay3D::Compose()
{
    mViewDisplay3D->resize( size() );
}


void
cProgram_ViewDisplay3D::Destroy()
{
    delete  mViewDisplay3D;
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// Registry Callback


QWidget*  RegistryCallback()
{
    return  new  cProgram_ViewDisplay3D();
}


} // namespace nViewDisplay3D
} // namespace nProgram

