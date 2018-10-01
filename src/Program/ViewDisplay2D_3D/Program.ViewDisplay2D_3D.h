/*************************************************************************
*
*   Lavabo
*__________________
*
* Program.ViewDisplay2D_3D.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


#include <QWidget>


class  cViewDisplay2D;
class  cViewDisplay3D;
class  cShader3D;
class  cModel3D;


class  QGraphicsProxyWidget;


namespace nProgram {
namespace nViewDisplay2D_3D {


class cProgram_ViewDisplay2D_3D :
    public QWidget
{
    Q_OBJECT

    typedef QWidget         tSuperClass;
    typedef cProgram_ViewDisplay2D_3D  tSelf;

public:
    // Construction / Destruction
    virtual  ~cProgram_ViewDisplay2D_3D();
    cProgram_ViewDisplay2D_3D( QWidget*  parent = NULL );

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
    cViewDisplay2D* mViewDisplay2D;
    cViewDisplay3D* mViewDisplay3D;
    QGraphicsProxyWidget* mProxyViewDisplay3D;
    cModel3D* mModel3D;
    cShader3D* mShader3D;
};


// Registry Callback
QWidget*  RegistryCallback();


} // namespace nViewDisplay2D_3D
} // namespace nProgram

