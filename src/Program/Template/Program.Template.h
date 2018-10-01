/*************************************************************************
*
*   Lavabo
*__________________
*
* Program.Template.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


#include <QWidget>


namespace nProgram {
namespace nTemplate {


class cTemplate :
    public QWidget
{
    Q_OBJECT

    typedef QWidget     tSuperClass;
    typedef cTemplate   tSelf;

public:
    // Construction / Destruction
    virtual  ~cTemplate();
    cTemplate( QWidget*  parent = NULL );

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
    QWidget* debug_widget;
};


// Registry Callback
QWidget*  RegistryCallback();


} // namespace nTemplate
} // namespace nProgram

