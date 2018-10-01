/*************************************************************************
*
*   Lavabo
*__________________
*
* ViewDisplay3D.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


#include <GL/glew.h>
#include <QOpenGLWidget>


#include <glm/mat4x4.hpp>


class cShader3D;
class cModel3D;


class QTimer;


class cViewDisplay3D :
    public QOpenGLWidget
{
    Q_OBJECT

    typedef QOpenGLWidget           tSuperClass;
    typedef cViewDisplay3D   tSelf;

public:
    // Construction / Destruction
    virtual  ~cViewDisplay3D();
    cViewDisplay3D( QWidget*  parent = NULL );

public:
    // Public View API
    void  SetModel3D( cModel3D* iModel );
    cModel3D* Model3D()  const;

    void  SetShader3D( cShader3D* iShader );
    cShader3D* Shader3D()  const;

protected:
    // Event
    virtual  void  resizeEvent( QResizeEvent*   event )     override;

protected:
    // GL
    virtual  void initializeGL() override;
    virtual  void resizeGL(int w, int h) override;
    virtual  void paintGL() override;

public:
    Q_SIGNAL void  PaintCompleted();

private:
    // GUI utilities
    void  Init();
    void  Build();
    void  Compose();
    void  Destroy();

private:
    // Private Data Members
    cModel3D* mModel3D;
    cShader3D* mShader3D;

    //QTimer* mTimer;

    glm::mat4 mModelMatrix;
    glm::mat4 mViewMatrix;
    glm::mat3 mNormalMatrix;
    glm::mat4 mProjectionMatrix;
};

