/*************************************************************************
*
*   Lavabo
*__________________
*
* ViewDisplay2D.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


#include <QGraphicsView>


class  QScroller;
class  QTimer;
class  QCursor;


class cViewDisplay2D :
    public QGraphicsView
{
    Q_OBJECT

    typedef QGraphicsView   tSuperClass;
    typedef cViewDisplay2D   tSelf;

public:
    // Construction / Destruction
    virtual  ~cViewDisplay2D();
    cViewDisplay2D( QWidget*  parent = NULL );

public:
    // Shadowing Behaviour
    QGraphicsScene* scene() const;
    void setScene(QGraphicsScene *scene);
    void setCenterItem( QGraphicsItem* item );
    QGraphicsItem* centerItem() const;

protected:
    // Event
    virtual  void  resizeEvent( QResizeEvent*  event )          override;
    virtual  void  keyPressEvent( QKeyEvent*  event )           override;
    virtual  void  keyReleaseEvent( QKeyEvent*  event )         override;
    virtual  void  mouseMoveEvent( QMouseEvent*  event )        override;
    virtual  void  mousePressEvent( QMouseEvent*  event )       override;
    virtual  void  mouseReleaseEvent( QMouseEvent*  event )     override;
    virtual  void  wheelEvent( QWheelEvent*  event )            override;

private:
    // TickSlot
    Q_SLOT void tickSlot();

private:
    // Interation Behaviours
    qreal   Scale();
    void    DeltaScale( qreal iDelta );
    void    SetScale( qreal iValue );

    bool    IsCenterItemFullyVisible();
    void    RecomputeSceneRectOnChange();

private:
    // GUI
    void Init();
    void Build();
    void Compose();
    void Destroy();

private:
    // Private Data Members
    QScroller*  mScroller;
    QTimer*     mTimer;
    QCursor*    mLensCursor;

    bool        mMoveModifierOn;
    bool        mZoomModifierOn;

    bool        mMouseMovedWhileMouseZoom;

    QString     mInteractionState;
    QString     mLastInteractionState;
    QPoint      mLastMousePos;
    QPoint      mTargetViewPos;
    QPointF     mTargetItemPos;

    //Scene
    QGraphicsScene* mScene;
    QGraphicsItem* mCenterItem;
};

