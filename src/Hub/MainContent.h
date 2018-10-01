/*************************************************************************
*
*   Lavabo
*__________________
*
* MainContent.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


#include <QWidget>


class  QListWidget;
class  QStackedWidget;


class  cHomeWidget;


class cMainContent :
    public QWidget
{
    Q_OBJECT

    typedef QWidget         tSuperClass;
    typedef cMainContent    tSelf;

public:
    struct cAccessibleChildren
    {
        QWidget* mLeftWidget;
        QWidget* mBotWidget;
        QListWidget* mLeftList;
        QStackedWidget*  mStackedWidget;
        cHomeWidget*    mHomeWidget;
    };

public:
    // Construction / Destruction
    virtual  ~cMainContent();
    cMainContent( QWidget*  parent = NULL );

public:
    // Accessible Children
    cAccessibleChildren  AccessibleChildren()  const;

protected:
    // Event
    virtual  void  resizeEvent( QResizeEvent*   event )     override;

private:
    // GUI utilities
    void  Init();
    void  Build();
    void  Compose();
    void  Destroy();

private:
    // Private Data Members
    QWidget* mLeftWidget;
    QWidget* mRightWidget;
    QWidget* mBotWidget;

    QListWidget* mLeftList;

    QStackedWidget*  mStackedWidget;
    cHomeWidget*    mHomeWidget;
};

