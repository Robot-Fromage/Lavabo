/*************************************************************************
*
*   Lavabo
*__________________
*
* HomeWidget.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "HomeWidget.h"


#include "ProgramButton.h"
#include "Program.ProgramRegistry.h"


#include <QScrollArea>
#include <QScrollBar>


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cHomeWidget::~cHomeWidget()
{
    Destroy();
}


cHomeWidget::cHomeWidget( QWidget*  parent ) :
    tSuperClass( parent ),
    mScrollArea( NULL ),
    mContentsWrapper( NULL ),
    mContents( NULL ),
    mProgramButtons( QVector< cProgramButton* >() )
{
    Init();
    Build();
    Compose();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------ Accessible Children


cHomeWidget::cAccessibleChildren
cHomeWidget::AccessibleChildren()  const
{
    return  cAccessibleChildren{
                mProgramButtons
            };
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Event


void
cHomeWidget::resizeEvent( QResizeEvent* event )
{
    tSuperClass::resizeEvent( event );
    Compose();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
cHomeWidget::Init()
{
    mScrollArea = new  QScrollArea( this );
    mContentsWrapper = new QWidget();
    mContents = new QWidget( mContentsWrapper );
}


void
cHomeWidget::Build()
{
    this->tSelf::setObjectName( "HomeWidget" );
    mScrollArea->setObjectName( "HomeWidget_ScrollArea" );
    mContentsWrapper->setObjectName( "HomeWidget_ContentsWrapper" );
    mContents->setObjectName( "HomeWidget_Contents" );

    mScrollArea->setWidget( mContentsWrapper );

    auto programList = ::nProgram::ProgramRegistry()->Keys();
    for ( auto it : programList )
    {
        auto p = new cProgramButton( it, mContents );
        mProgramButtons.append( p );
    }
}


void
cHomeWidget::Compose()
{
    int w = size().width();
    int h = size().height();

    mScrollArea->resize( size() );

    int btn_padding = 5;
    int btn_width = 150;
    int btn_height = 150;
    int content_padding = 10;

    int contentsWrapper_width = mScrollArea->width() - 1;
    int content_width = contentsWrapper_width - 2 * content_padding;

    int nBtn = mProgramButtons.length();
    int nBtn_per_line = content_width / ( btn_width + btn_padding );
    int nBtn_rows = ceil( double( nBtn ) / double( nBtn_per_line ) );

    int content_height = nBtn_rows * ( btn_height + btn_padding );
    int contentsWrapper_height = content_height + 2 * content_padding;

    mContentsWrapper->resize( contentsWrapper_width, contentsWrapper_height );
    mContents->resize( content_width, content_height );
    mContents->move( content_padding, content_padding );

    for( int i = 0; i < mProgramButtons.length(); ++i )
    {
        int col = i % nBtn_per_line;
        int row = i / nBtn_per_line;

        mProgramButtons[i]->resize( btn_width, btn_height );
        mProgramButtons[i]->move( col * ( btn_width + btn_padding ), row * ( btn_height + btn_padding ) );
    }
}


void
cHomeWidget::Destroy()
{
    delete  mScrollArea;

    for( auto it : mProgramButtons )
    {
        delete  it;
    }
}