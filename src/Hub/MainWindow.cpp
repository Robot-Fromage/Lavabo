/*************************************************************************
*
*   Lavabo
*__________________
*
* MainWindow.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "MainWindow.h"


#include <QListWidget>
#include <QStackedWidget>


#include "MainCaption.h"
#include "MainContent.h"
#include "HomeWidget.h"
#include "ProgramButton.h"
#include "Program.ProgramRegistry.h"


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cMainWindow::~cMainWindow()
{
    Destroy();
}


cMainWindow::cMainWindow( QWidget*  parent ) :
    tSuperClass( parent ),
    mMainCaptionWidget( NULL ),
    mMainContentWidget( NULL )
{
    tSelf::Init();
    tSelf::Build();
    tSelf::Compose();
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------- Private Slots API


void
cMainWindow::CreateProgram( QString iStr )
{
    auto nu = ::nProgram::ProgramRegistry()->GetProgram( iStr );

    if( !nu )
        return;

    nu->setAttribute( Qt::WA_DeleteOnClose );

    auto t = new ::Rivet::Tab();
    t->SetLinkWidget( nu );
    t->SetColor( QColor( 25, 30, 34 ) );
    t->SetFadeColor( QColor( 18, 21, 24 ) );
    t->SetTitle( iStr );
    t->SetTag( "main" );
    mMainCaptionWidget->AccessibleChildren().mTabArea->DockHere( t );
}


void
cMainWindow::CreateProgram( QListWidgetItem* iItem )
{
    CreateProgram( iItem->text() );
}


void
cMainWindow::ProcessHomeClicked()
{
    mMainContentWidget->AccessibleChildren().mStackedWidget->setCurrentWidget(
        mMainContentWidget->AccessibleChildren().mHomeWidget );

    mMainCaptionWidget->AccessibleChildren().mTabArea->SetCurrentTab( NULL );
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
cMainWindow::Init()
{
    mMainCaptionWidget = new cMainCaption( NULL );
    mMainContentWidget = new cMainContent( NULL );
}


void
cMainWindow::Build()
{
    setMinimumSize( 400, 120 );

    tSuperClass::SetCaptionHeight( 60 );
    tSuperClass::SetCaptionWidget( mMainCaptionWidget );
    tSuperClass::SetCenterWidget( mMainContentWidget );

    QObject::connect(
        mMainContentWidget->AccessibleChildren().mLeftList,
        SIGNAL( itemDoubleClicked( QListWidgetItem* ) ),
        this,
        SLOT( CreateProgram( QListWidgetItem* ) ) );

    QObject::connect(
        mMainCaptionWidget->AccessibleChildren().mBtnHome,
        SIGNAL( pressed() ),
        this,
        SLOT( ProcessHomeClicked() ) );

    // Icon program buttons in home tab
    auto programButtons = mMainContentWidget->AccessibleChildren().mHomeWidget->AccessibleChildren().mProgramButtons;
    for( auto it : programButtons )
    {
        QObject::connect(
            it,
            SIGNAL( DoubleClicked( QString ) ),
            this,
            SLOT( CreateProgram( QString ) ) );
    }

    mMainCaptionWidget->AccessibleChildren().mTabArea->SetLinkedStack(
        mMainContentWidget->AccessibleChildren().mStackedWidget );
}


void
cMainWindow::Compose()
{
    // NOTHING ATM
}


void
cMainWindow::Destroy()
{
    delete  mMainCaptionWidget;
    delete  mMainContentWidget;
}
