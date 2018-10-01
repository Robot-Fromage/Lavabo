/*************************************************************************
*
*   Lavabo
*__________________
*
* Program.Template.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "Program.Template.h"


namespace nProgram {
namespace nTemplate {


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cTemplate::~cTemplate()
{
    Destroy();
}


cTemplate::cTemplate( QWidget*  parent ) :
    tSuperClass( parent ),
    debug_widget( NULL )
{
    Init();
    Build();
    Compose();
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Event


void
cTemplate::resizeEvent( QResizeEvent* event )
{
    tSuperClass::resizeEvent( event );
    Compose();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
cTemplate::Init()
{
    debug_widget = new QWidget( this );
}


void
cTemplate::Build()
{
    debug_widget->setStyleSheet( "background: rgb( 20, 20, 20 );" );
}


void
cTemplate::Compose()
{
    debug_widget->resize( size() );
}


void
cTemplate::Destroy()
{
    delete  debug_widget;
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// Registry Callback


QWidget*  RegistryCallback()
{
    return  new  cTemplate();
}


} // namespace nTemplate
} // namespace nProgram

