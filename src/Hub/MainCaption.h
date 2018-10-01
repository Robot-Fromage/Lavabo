/*************************************************************************
*
*   Lavabo
*__________________
*
* MainCaption.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE
*/

#pragma once


#include <RivetCustomCaption>
#include <RivetCustomButton>
#include <RivetTabArea>


class  QLabel;
class  QPixmap;
class  QPushButton;

class cMainCaption :
    public ::Rivet::CustomCaption
{
    Q_OBJECT

    typedef ::Rivet::CustomCaption  tSuperClass;
    typedef cMainCaption            tSelf;

public:
    struct cAccessibleChildren
    {
        QWidget*                mTitleBackground;
        QWidget*                mCaptionBackground;
        ::Rivet::CustomButton*  mCloseButton;
        ::Rivet::CustomButton*  mMaximizeButton;
        ::Rivet::CustomButton*  mMinimizeButton;
        QPixmap*                mTitleImage;
        QLabel*                 mTitle;
        QPushButton*            mBtnHome;
        ::Rivet::TabArea*       mTabArea;
    };

public:
    // Construction / Destruction
    virtual  ~cMainCaption();
    cMainCaption( QWidget*  parent = NULL );

public:
    // Accessible Children
    cAccessibleChildren  AccessibleChildren()  const;

public:
    // HitTest override
    virtual  bool  HitEmptySpace( long iX, long iY )  override;

protected:
    // Protected Qt event overrides
    virtual  void  resizeEvent( QResizeEvent*   event )     override;

private:
    // GUI utilities
    void  Init();
    void  Build();
    void  Compose();
    void  Destroy();

private:
    // Private Data Members
    QWidget* mTitleBackground;
    QWidget* mCaptionBackground;

    ::Rivet::CustomButton*  mCloseButton;
    ::Rivet::CustomButton*  mMaximizeButton;
    ::Rivet::CustomButton*  mMinimizeButton;

    QPixmap* mTitleImage;
    QLabel* mTitle;

    QPushButton*  mBtnHome;
    ::Rivet::TabArea*  mTabArea;
};

