/*************************************************************************
*
*   Lavabo
*__________________
*
* Program.ViewDisplay3D.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


#include <QWidget>


class cViewDisplay3D;
class cShader3D;
class cModel3D;


namespace nProgram {
namespace nViewDisplay3D {


class cProgram_ViewDisplay3D :
    public QWidget
{
    Q_OBJECT

    typedef QWidget                 tSuperClass;
    typedef cProgram_ViewDisplay3D  tSelf;

public:
    // Construction / Destruction
    virtual  ~cProgram_ViewDisplay3D();
    cProgram_ViewDisplay3D( QWidget*  parent = NULL );

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
    cViewDisplay3D* mViewDisplay3D;
    cModel3D* mModel3D;
    cShader3D* mShader3D;
};


// Registry Callback
QWidget*  RegistryCallback();


} // namespace nViewDisplay3D
} // namespace nProgram

