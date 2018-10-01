/*************************************************************************
*
*   Lavabo
*__________________
*
* MainWindow.h
* 3-10-2018 15:44 GMT+1
* Clement Berthaud - Layl
* Please refer to LICENSE
*/

#pragma once


#include <RivetCustomMainWindow>


class QListWidgetItem;

class cMainCaption;
class cMainContent;


class cMainWindow :
    public ::Rivet::CustomMainWindow
{
    Q_OBJECT

    typedef ::Rivet::CustomMainWindow   tSuperClass;
    typedef cMainWindow                 tSelf;

public:
    // Construction / Destruction
    virtual  ~cMainWindow();
    cMainWindow( QWidget*  parent = NULL );

private slots:
    // Private Slots API
    void  CreateProgram( QString iStr );
    void  CreateProgram( QListWidgetItem* iItem );
    void  ProcessHomeClicked();

private:
    // GUI utilities
    void  Init();
    void  Build();
    void  Compose();
    void  Destroy();

private:
    cMainCaption* mMainCaptionWidget;
    cMainContent* mMainContentWidget;

};

