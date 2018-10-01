/*************************************************************************
*
*   Lavabo
*__________________
*
* Program.ViewDisplay2D.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "Program.ViewDisplay2D.h"


#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGuiApplication>
#include <QWheelEvent>


namespace nProgram {
namespace nViewDisplay2D {


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cProgram_ViewDisplay2D::~cProgram_ViewDisplay2D()
{
    Destroy();
}


cProgram_ViewDisplay2D::cProgram_ViewDisplay2D( QWidget*  parent ) :
    tSuperClass( parent ),
    mView( NULL ),
    mPixmap( NULL )
{
    Init();
    Build();
    Compose();
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Event


void
cProgram_ViewDisplay2D::resizeEvent( QResizeEvent* event )
{
    tSuperClass::resizeEvent( event );
    Compose();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
cProgram_ViewDisplay2D::Init()
{
    mView = new cViewDisplay2D( this );

    mPixmap = new QPixmap( "resources/media/img/program_specific/ViewDisplay2D/sample.png" );
}


void
cProgram_ViewDisplay2D::Build()
{
    mView->setCenterItem( new QGraphicsPixmapItem( *mPixmap ) );
}


void
cProgram_ViewDisplay2D::Compose()
{
    mView->resize( size() );
}


void
cProgram_ViewDisplay2D::Destroy()
{
    delete  mView;
    delete  mPixmap;
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// Registry Callback


QWidget*  RegistryCallback()
{
    return  new  cProgram_ViewDisplay2D();
}


} // namespace nViewDisplay2D
} // namespace nProgram

