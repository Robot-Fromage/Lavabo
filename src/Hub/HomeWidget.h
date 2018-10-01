/*************************************************************************
*
*   Lavabo
*__________________
*
* HomeWidget.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE
*/

#pragma once


#include <QWidget>


class cProgramButton;
class QScrollArea;


class cHomeWidget :
    public QWidget
{
    Q_OBJECT

    typedef QWidget         tSuperClass;
    typedef cHomeWidget     tSelf;

public:
    struct cAccessibleChildren
    {
        QVector< cProgramButton* > mProgramButtons;
    };

public:
    // Construction / Destruction
    virtual  ~cHomeWidget();
    cHomeWidget( QWidget*  parent = NULL );

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
    QScrollArea* mScrollArea;
    QWidget* mContentsWrapper;
    QWidget* mContents;

    QVector< cProgramButton* > mProgramButtons;
};

