/*************************************************************************
*
*   Lavabo
*__________________
*
* MainCaption.cpp
* 3-10-2018 17:13 GMT+1
* Clement Berthaud - Layl
* Please refer to LICENSE
*/

#include "MainCaption.h"


#include <RivetDockingCallbackLibrary>


#include <QLabel>
#include <QPixmap>
#include <QPushButton>

//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cMainCaption::~cMainCaption()
{
    tSelf::Destroy();
}


cMainCaption::cMainCaption( QWidget*  parent ) :
    tSuperClass( parent ),
    mTitleBackground(   NULL ),
    mCaptionBackground( NULL ),
    mCloseButton(       NULL ),
    mMaximizeButton(    NULL ),
    mMinimizeButton(    NULL ),
    mTitleImage(        NULL ),
    mTitle(             NULL ),
    mBtnHome(           NULL ),
    mTabArea(           NULL )
{
    tSelf::Init();
    tSelf::Build();
    tSelf::Compose();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------ Accessible Children


cMainCaption::cAccessibleChildren
cMainCaption::AccessibleChildren()  const
{
    return  cAccessibleChildren{
                mTitleBackground,
                mCaptionBackground,
                mCloseButton,
                mMaximizeButton,
                mMinimizeButton,
                mTitleImage,
                mTitle,
                mBtnHome,
                mTabArea,
            };
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------- HitTest override


bool
cMainCaption::HitEmptySpace( long iX, long iY )
{
    QPoint local( iX, iY );
    bool result = true;

    QList< QWidget* > list = this->findChildren< QWidget* >();

    // If a direct child contains our mouse coordinates, we refute.
    for each( QWidget* w in list ) {
        QRect g = w->geometry();
        if( g.contains( local ) && w->parent() == this )
        {
            // But we accept title
            if( w == mTitleBackground ) continue;
            if( w == mCaptionBackground ) continue;
            if( w == mTitle ) continue;

            result = false;
        }
    }

    // But if it is the tab area, we ask it for more details.
    if( result == false && mTabArea->geometry().contains( local ) )
        result = mTabArea->HitEmptySpace( local.x(), local.y() );

    return  result;
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------- Protected Qt event overrides


void
cMainCaption::resizeEvent( QResizeEvent *event )
{
    tSuperClass::resizeEvent(event);
    Compose();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
cMainCaption::Init()
{
    mTitleBackground = new QWidget( this );
    mCaptionBackground = new QWidget( this );

    if( !mCloseButton )     mCloseButton    = new  ::Rivet::CustomButton( this );
    if( !mMaximizeButton )  mMaximizeButton = new  ::Rivet::CustomButton( this );
    if( !mMinimizeButton )  mMinimizeButton = new  ::Rivet::CustomButton( this );

    mTitleImage = new QPixmap( "resources/media/img/title.png" );
    mTitle = new QLabel( this );

    mTabArea = new ::Rivet::TabArea( this );
    mBtnHome = new QPushButton( this );
}


void
cMainCaption::Build()
{
    mTitleBackground->setObjectName( "MainCaption_TitleBackground" );
    mCaptionBackground->setObjectName( "MainCaption_CaptionBackground" );
    mTitle->setObjectName( "MainCaption_Title" );
    mBtnHome->setObjectName( "MainCaption_BtnHome" );
    mTabArea->setObjectName( "MainCaption_TabArea" );

    mCloseButton->SetShape( ::Rivet::CustomButton::eShape::kClose );
    mMaximizeButton->SetShape( ::Rivet::CustomButton::eShape::kMaximize );
    mMinimizeButton->SetShape( ::Rivet::CustomButton::eShape::kMinimize );

    QObject::connect( mCloseButton, SIGNAL( clicked() ), this, SLOT( ProcessCloseClicked() ) );
    QObject::connect( mMaximizeButton, SIGNAL( clicked() ), this, SLOT( ProcessMaximizeClicked() ) );
    QObject::connect( mMinimizeButton, SIGNAL( clicked() ), this, SLOT( ProcessMinimizeClicked() ) );

    mCloseButton->SetSize( 9 );
    mMaximizeButton->SetSize( 9 );
    mMinimizeButton->SetSize( 9 );

    QColor col( 220, 220, 220 );
    mCloseButton->SetColor( col );
    mCloseButton->SetHoveredColor( col );
    mCloseButton->SetPressedColor( col );

    mMaximizeButton->SetColor( col );
    mMaximizeButton->SetHoveredColor( col );
    mMaximizeButton->SetPressedColor( col );

    mMinimizeButton->SetColor( col );
    mMinimizeButton->SetHoveredColor( col );
    mMinimizeButton->SetPressedColor( col );

    QColor hbg( 25, 30, 34 );
    mCloseButton->SetHoveredBackgroundColor( QColor( 110, 45, 27 ) );
    mMaximizeButton->SetHoveredBackgroundColor( hbg );
    mMinimizeButton->SetHoveredBackgroundColor( hbg );

    mCloseButton->SetPressedBackgroundColor( QColor( 54, 17, 6 ) );
    mMaximizeButton->SetPressedBackgroundColor( Qt::black );
    mMinimizeButton->SetPressedBackgroundColor( Qt::black );

    mTitle->setPixmap( *mTitleImage );

    mTabArea->SetOverlap( 20 );
    mTabArea->SetOnTabDroppedOutCB( ::Rivet::OnTabDroppedOutCB_RevertBack );
    mTabArea->SetTag( "main" );
    mTabArea->SetTabsLiftable( true );
    mTabArea->SetTabsClosable( true );

    mTabArea->SetCurrentTab( NULL );

    // prevent trigger by press space
    mMinimizeButton->setFocusPolicy( Qt::NoFocus );
    mMaximizeButton->setFocusPolicy( Qt::NoFocus );
    mCloseButton->setFocusPolicy( Qt::NoFocus );
}


void
cMainCaption::Compose()
{
    int w = width();
    int h = height();
    int h2 = h / 2;

    int title_width = 200;
    mTitleBackground->resize( title_width, h );
    mCaptionBackground->setGeometry( title_width, 0, w - title_width, h );

    auto titlesizehint = mTitle->sizeHint();
    int titleph = ( title_width - titlesizehint.width() ) / 2;
    int titlepv = ( h - titlesizehint.height() ) / 2;
    mTitle->resize( titlesizehint );
    mTitle->move( titleph, titlepv );

    float buttonRatio   = 1.5f;
    int buttonHeight    = h2;
    int buttonWidth     = buttonHeight * buttonRatio;

    QSize buttonSize( buttonWidth, buttonHeight );
    mCloseButton->resize( buttonSize );
    mMaximizeButton->resize( buttonSize );
    mMinimizeButton->resize( buttonSize );

    int n = 0;
    mCloseButton->move(     w - buttonWidth * ++n, 0 );
    mMaximizeButton->move(  w - buttonWidth * ++n, 0 );
    mMinimizeButton->move(  w - buttonWidth * ++n, 0 );

    mBtnHome->resize( 40, 30 );
    mBtnHome->move( title_width, 30 );

    mTabArea->resize( w - title_width - 26, h2 );
    mTabArea->move( title_width + 26, h2 + 1 );
}


void
cMainCaption::Destroy()
{
    delete  mTitleBackground;
    delete  mCaptionBackground;

    delete  mCloseButton;
    delete  mMaximizeButton;
    delete  mMinimizeButton;

    delete  mTitleImage;
    delete  mTitle;

    delete  mBtnHome;
    delete  mTabArea;
}