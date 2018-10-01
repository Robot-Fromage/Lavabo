/*************************************************************************
*
*   Lavabo
*__________________
*
* MainContent.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "MainContent.h"


#include <QListWidget>
#include <QStackedWidget>


#include "HomeWidget.h"
#include "Program.ProgramRegistry.h"


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cMainContent::~cMainContent()
{
    Destroy();
}


cMainContent::cMainContent( QWidget*  parent ) :
    tSuperClass( parent ),
    mLeftWidget( NULL ),
    mBotWidget( NULL ),
    mLeftList( NULL ),
    mStackedWidget( NULL ),
    mHomeWidget( NULL )
{
    Init();
    Build();
    Compose();
}

//--------------------------------------------------------------------------------------
//------------------------------------------------------------------ Accessible Children


cMainContent::cAccessibleChildren
cMainContent::AccessibleChildren()  const
{
    return  cAccessibleChildren{
                mLeftWidget,
                mBotWidget,
                mLeftList,
                mStackedWidget,
                mHomeWidget,
            };
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Event


void
cMainContent::resizeEvent( QResizeEvent* event )
{
    tSuperClass::resizeEvent( event );
    Compose();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
cMainContent::Init()
{
    mLeftWidget = new QWidget( this );
    mBotWidget = new QWidget( this );

    mLeftList = new  QListWidget( mLeftWidget );

    mStackedWidget = new  QStackedWidget( this );
    mHomeWidget = new cHomeWidget( NULL );

}


void
cMainContent::Build()
{
    mLeftWidget->setObjectName( "MainContent_LeftWidget" );
    mBotWidget->setObjectName( "MainContent_BotWidget" );
    mLeftList->setObjectName( "MainContent_LeftList" );
    mStackedWidget->setObjectName( "MainContent_StackedWidget" );

    mLeftList->setAlternatingRowColors( true );
    mLeftList->setFocusPolicy( Qt::NoFocus );

    auto programList = ::nProgram::ProgramRegistry()->Keys();
    for ( auto it : programList )
    {
        mLeftList->addItem( it );
    }

    mStackedWidget->addWidget( mHomeWidget );
    mStackedWidget->setCurrentWidget( mHomeWidget );
}


void
cMainContent::Compose()
{
    int w = width();
    int h = height();

    int left_width = 200;
    int bottom_height = 10;
    int available_height = h -bottom_height;

    mLeftWidget->resize( left_width, available_height );

    mStackedWidget->resize( w - left_width, available_height );
    mStackedWidget->move( left_width, 0 );

    mBotWidget->resize( w, bottom_height );
    mBotWidget->move( 0, available_height );

    {
        mLeftList->move( 0, 10 );
        mLeftList->resize( left_width, available_height - 20 );
    }
}


void
cMainContent::Destroy()
{
    delete  mLeftList;

    delete  mLeftWidget;
    delete  mBotWidget;

    delete  mStackedWidget;
    delete  mHomeWidget;
}