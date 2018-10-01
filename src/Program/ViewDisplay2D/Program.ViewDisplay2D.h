/*************************************************************************
*
*   Lavabo
*__________________
*
* Program.ViewDisplay2D.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


#include <QWidget>


#include "ViewDisplay2D.h"


#include <QPixmap>


namespace nProgram {
namespace nViewDisplay2D {


class cProgram_ViewDisplay2D :
    public QWidget
{
    Q_OBJECT

    typedef QWidget         tSuperClass;
    typedef cProgram_ViewDisplay2D  tSelf;

public:
    // Construction / Destruction
    virtual  ~cProgram_ViewDisplay2D();
    cProgram_ViewDisplay2D( QWidget*  parent = NULL );

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
    cViewDisplay2D* mView;
    QPixmap*        mPixmap;
};


// Registry Callback
QWidget*  RegistryCallback();


} // namespace nViewDisplay2D
} // namespace nProgram

