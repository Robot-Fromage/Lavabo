/*************************************************************************
*
*   Lavabo
*__________________
*
* ProgramButton.cpp
* 3-10-2018 14:35 GMT+1
* Clement Berthaud - Layl
* Please refer to LICENSE
*/

#include "ProgramButton.h"


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cProgramButton::~cProgramButton()
{
    Destroy();
}


cProgramButton::cProgramButton( const QString& iKey, QWidget*  parent ) :
    tSuperClass( parent ),
    mKey( iKey ),
    mImageLabel( NULL ),
    mImage( NULL ),
    mTextLabel( NULL ),
    mOverlay( NULL )
{
    Init();
    Build();
    Compose();
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Event


void
cProgramButton::resizeEvent( QResizeEvent* event )
{
    tSuperClass::resizeEvent( event );
    Compose();
}


void
cProgramButton::mouseDoubleClickEvent( QMouseEvent*  event )
{
    emit  DoubleClicked( mKey );
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
cProgramButton::Init()
{
    QString prefix = "resources/media/img/program_icon/";
    QString suffix = ".png";
    QString img_path = prefix + mKey + suffix;

    mImageLabel = new QLabel( this );
    mImage = new QPixmap( img_path );
    mTextLabel = new QLabel( this );

    mOverlay = new QWidget( this );
}


void
cProgramButton::Build()
{
    this->tSelf::setObjectName( "ProgramButton" );
    mImageLabel->setObjectName( "ProgramButton_ImageLabel" );
    mTextLabel->setObjectName( "ProgramButton_TextLabel" );

    mOverlay->setObjectName( "ProgramButton_Overlay" );

    mImageLabel->setPixmap( *mImage );
    mTextLabel->setText( mKey );
}


void
cProgramButton::Compose()
{
    int w = width();
    int h = height();

    auto imageLabelSizeHint = mImageLabel->sizeHint();
    auto imageLabelPadH = ( w - imageLabelSizeHint.width() ) / 2;
    auto imageLabelPadV = 10;
    mImageLabel->resize( imageLabelSizeHint );
    mImageLabel->move( imageLabelPadH, imageLabelPadV );

    int rep = mImageLabel->geometry().bottom();
    auto textLabelSizeHint = mTextLabel->sizeHint();
    auto textLabelPadH = ( w - textLabelSizeHint.width() ) / 2;
    auto textLabelPadV = ( ( h - rep ) - textLabelSizeHint.height() ) / 2;
    mTextLabel->resize( textLabelSizeHint );
    mTextLabel->move( textLabelPadH, rep + textLabelPadV );

    mOverlay->resize( w, h );
}


void
cProgramButton::Destroy()
{
    delete  mImageLabel;
    delete  mImage;
    delete  mTextLabel;

    delete  mOverlay;
}