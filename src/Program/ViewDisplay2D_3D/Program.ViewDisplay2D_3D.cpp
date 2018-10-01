/*************************************************************************
*
*   Lavabo
*__________________
*
* Program.ViewDisplay2D_3D.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "Program.ViewDisplay2D_3D.h"


#include <QGraphicsItem>
#include <QGraphicsProxyWidget>


#include "ViewDisplay2D.h"
#include "ViewDisplay3D.h"
#include "Model3D.h"
#include "Shader3D.h"


namespace nProgram {
namespace nViewDisplay2D_3D {


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cProgram_ViewDisplay2D_3D::~cProgram_ViewDisplay2D_3D()
{
    Destroy();
}


cProgram_ViewDisplay2D_3D::cProgram_ViewDisplay2D_3D( QWidget*  parent ) :
    tSuperClass( parent ),
    mViewDisplay2D( NULL ),
    mViewDisplay3D( NULL ),
    mProxyViewDisplay3D( NULL ),
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
cProgram_ViewDisplay2D_3D::resizeEvent( QResizeEvent* event )
{
    tSuperClass::resizeEvent( event );
    Compose();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
cProgram_ViewDisplay2D_3D::Init()
{
    mViewDisplay2D = new cViewDisplay2D( this );
    mViewDisplay3D = new cViewDisplay3D();
    mProxyViewDisplay3D = new QGraphicsProxyWidget();

    mModel3D = new cModel3D( "resources/obj3d/bunny.obj");
    mShader3D = new cShader3D( "resources/shaders/ViewDisplay3D.vert", "resources/shaders/ViewDisplay3D.frag" );
}


void
cProgram_ViewDisplay2D_3D::Build()
{
    mViewDisplay3D->SetModel3D( mModel3D );
    mViewDisplay3D->SetShader3D( mShader3D );
    mProxyViewDisplay3D->setWidget( mViewDisplay3D );
    mViewDisplay2D->setCenterItem( mProxyViewDisplay3D );

    //QObject::connect( mViewDisplay3D, SIGNAL( PaintCompleted() ), mViewDisplay2D, SLOT( update() ) );
}


void
cProgram_ViewDisplay2D_3D::Compose()
{
    mViewDisplay3D->resize( size() );
    mProxyViewDisplay3D->resize( size() );
    mViewDisplay2D->resize( size() );
}


void
cProgram_ViewDisplay2D_3D::Destroy()
{
    delete  mViewDisplay2D;
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// Registry Callback


QWidget*  RegistryCallback()
{
    return  new  cProgram_ViewDisplay2D_3D();
}


} // namespace nViewDisplay2D_3D
} // namespace nProgram

