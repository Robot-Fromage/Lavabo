/*************************************************************************
*
*   Lavabo
*__________________
*
* ViewDisplay2D.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "ViewDisplay2D.h"


#include <QEasingCurve>
#include <QDesktopWidget>
#include <QGuiApplication>
#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QEvent>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QScroller>
#include <QTimer>
#include <QCursor>
#include <QTransform>


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cViewDisplay2D::~cViewDisplay2D()
{
    Destroy();
}


cViewDisplay2D::cViewDisplay2D( QWidget*  parent ) :
    tSuperClass( parent ),
    mScroller( NULL ),
    mTimer( NULL ),
    mLensCursor( NULL ),
    mMoveModifierOn( false ),
    mZoomModifierOn( false ),
    mMouseMovedWhileMouseZoom( false ),
    mInteractionState( "none" ),
    mLastInteractionState( "none" ),
    mLastMousePos( QPoint() ),
    mTargetViewPos( QPoint() ),
    mTargetItemPos( QPointF() ),
    mScene( NULL ),
    mCenterItem( NULL )
{
    Init();
    Build();
    Compose();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------ Shadowing Behaviour


QGraphicsScene*
cViewDisplay2D::scene() const
{
    return  NULL;
}


void
cViewDisplay2D::setScene(QGraphicsScene *scene)
{
    // Nothing
}


void
cViewDisplay2D::setCenterItem( QGraphicsItem* item )
{
    //we take ownership of item

    if( mCenterItem )
    {
        // take back ownership of item from mScene
        mScene->removeItem( mCenterItem );
        delete mCenterItem;
        mCenterItem = 0;
    }

    mCenterItem = item;

    // mScene takes ownership of item
    if( mCenterItem  )
        mScene->addItem( mCenterItem );

    RecomputeSceneRectOnChange();
}


QGraphicsItem*
cViewDisplay2D::centerItem() const
{
    return  mCenterItem;
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Event


void
cViewDisplay2D::resizeEvent( QResizeEvent*  event )
{
    tSuperClass::resizeEvent( event );
    Compose();
}


void
cViewDisplay2D::keyPressEvent( QKeyEvent*   event )
{
    // Custom modifier Listen: Space
    if( event->key() == Qt::Key_Space )
        mMoveModifierOn = true;

    // Custom modifier Listen: Control
    if( event->key() == Qt::Key_Control )
        mZoomModifierOn = true;

    // Zoom Reset
    if( event->key() == Qt::Key_1 && mZoomModifierOn )
    {
        SetScale( 1.0 );
    }

    // Zoom Reset
    if( event->key() == Qt::Key_Plus && mZoomModifierOn )
    {
        qreal scale = Scale();

        qreal delta = 0.1;
        if( scale >= 1.0 )
            delta = 1.0;
        if( scale >= 8.0 )
            delta = 4.0;
        if( scale >= 32.0 )
            delta = 0.0;

        DeltaScale( delta );
    }

    // Zoom Reset
    if( event->key() == Qt::Key_Minus && mZoomModifierOn )
    {
        qreal scale = Scale();

        qreal delta = -4.0;
        if( scale < 8.0 )
            delta = -1.0;
        if( scale < 2.0 )
            delta = -0.1;
        if( scale < 0.01 )
            delta = 0.0;

        DeltaScale( delta );
    }
}


void
cViewDisplay2D::keyReleaseEvent( QKeyEvent*   event )
{
    // Custom modifier Listen: Space
    if( event->key() == Qt::Key_Space && !event->isAutoRepeat() )
        mMoveModifierOn = false;

    // Custom modifier Listen: Control
    if( event->key() == Qt::Key_Control && !event->isAutoRepeat() )
        mZoomModifierOn = false;
}


void
cViewDisplay2D::mouseMoveEvent( QMouseEvent*   event )
{
    if( mInteractionState == "mouse_zoom" && event->buttons().testFlag( Qt::LeftButton ) )
    {
        mMouseMovedWhileMouseZoom = true;

        float lastx = mLastMousePos.x();
        float curx = event->pos().x();
        float deltax = curx - lastx;
        qreal delta = deltax / 500 * ( Scale() + 1.0 );

        DeltaScale( delta );

        QPointF targetScenePos = mCenterItem->mapToScene( mTargetItemPos );
        centerOn( targetScenePos );
        QPointF delta_viewport_pos = mTargetViewPos - QPointF(  viewport()->width() / 2.0,
                                                                viewport()->height() / 2.0 );
        QPointF viewport_center = mapFromScene( targetScenePos ) - delta_viewport_pos;
        centerOn( mapToScene( viewport_center.toPoint() ) );
    }

    mLastMousePos = event->pos();
}


void
cViewDisplay2D::mousePressEvent( QMouseEvent*   event )
{
    mTargetViewPos = event->pos();
    mTargetItemPos = mCenterItem->mapFromScene( mapToScene( event->pos() ) );
    mLastMousePos = event->pos();
}


void
cViewDisplay2D::mouseReleaseEvent( QMouseEvent*   event )
{
    if( mInteractionState == "mouse_zoom" && !mMouseMovedWhileMouseZoom )
    {
        qreal scale = Scale();

        qreal delta = 0.1;
        if( scale >= 1.0 )
            delta = 1.0;
        if( scale >= 8.0 )
            delta = 4.0;
        if( scale >= 32.0 )
            delta = 0.0;

        DeltaScale( delta );
    }

    mMouseMovedWhileMouseZoom = false;
}


void
cViewDisplay2D::wheelEvent( QWheelEvent*   event )
{
    if( mInteractionState == "mouse_zoom" )
        return;

    if( mInteractionState == "key_zoom" )
    {
        mTargetViewPos = event->pos();
        mTargetItemPos = mCenterItem->mapFromScene( mapToScene( event->pos() ) );

        DeltaScale( double( event->delta() ) / 1000.0 * ( Scale() + 1.0 ) );

        QPointF targetScenePos = mCenterItem->mapToScene( mTargetItemPos );
        centerOn( targetScenePos );
        QPointF delta_viewport_pos = mTargetViewPos - QPointF(  viewport()->width() / 2.0,
                                                                viewport()->height() / 2.0 );
        QPointF viewport_center = mapFromScene( targetScenePos ) - delta_viewport_pos;
        centerOn( mapToScene( viewport_center.toPoint() ) );
        return;
    }

    tSuperClass::wheelEvent( event );
}

//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- TickSlot


void
cViewDisplay2D::tickSlot()
{
    QString decide_state = "none";

    // Decide
    if( mMoveModifierOn && !mZoomModifierOn )
        decide_state = "mouse_move";

    if( mZoomModifierOn )
        decide_state = "key_zoom";

    if( mMoveModifierOn && mZoomModifierOn )
        decide_state = "mouse_zoom";

    if( mLastInteractionState == "mouse_move" && QGuiApplication::mouseButtons().testFlag( Qt::MouseButton::LeftButton ) )
        decide_state = "mouse_move";

    // Apply
    if( decide_state == "none" )
    {
        mScroller->ungrabGesture( viewport() );
        setCursor( Qt::ArrowCursor );
    }
    else if( decide_state == "mouse_move" )
    {

        if( !IsCenterItemFullyVisible() )
            mScroller->grabGesture( viewport(), QScroller::LeftMouseButtonGesture );

        if( QGuiApplication::mouseButtons().testFlag( Qt::MouseButton::LeftButton ) )
            setCursor( Qt::ClosedHandCursor );
        else
            setCursor( Qt::OpenHandCursor );
    }
    else if( decide_state == "mouse_zoom" )
    {
        mScroller->ungrabGesture( viewport() );
        setCursor( *mLensCursor );
    }
    else if( decide_state == "key_zoom" )
    {
        setCursor( Qt::CrossCursor );
    }

    // Update if necessary
    if( decide_state != mLastInteractionState )
        repaint();

    // Finally set flags
    mInteractionState = decide_state;
    mLastInteractionState = mInteractionState;
}


//--------------------------------------------------------------------------------------
//---------------------------------------------------------------- Interation Behaviours


qreal
cViewDisplay2D::Scale()
{
    return  transform().m11(); // same as t.m22()
}


void
cViewDisplay2D::DeltaScale( qreal iDelta )
{
        QTransform t = transform();
        qreal oldscale = t.m11(); // same as t.m22()
        qreal new_scale = oldscale + iDelta;

        if( new_scale >= 32.0 )
            new_scale = 32.0;

        if( new_scale < 0.01 )
            new_scale = 0.01;

        qreal factor = new_scale / oldscale;

        t.scale( factor, factor );
        setTransform( t );

        RecomputeSceneRectOnChange();
}


void
cViewDisplay2D::SetScale( qreal iValue )
{
        QTransform t = transform();
        qreal old_scale = t.m11(); // both
        qreal new_scale = iValue;
        qreal factor = new_scale / old_scale;

        t.scale( factor, factor );
        setTransform( t );

        RecomputeSceneRectOnChange();
}


bool
cViewDisplay2D::IsCenterItemFullyVisible()
{
    auto ir = mCenterItem->boundingRect();
    return  ir.width() * Scale() <= viewport()->width() && ir.height() * Scale() <= viewport()->height();
}


void
cViewDisplay2D::RecomputeSceneRectOnChange()
{
    if( !mCenterItem )
        return;

    if( IsCenterItemFullyVisible() )
    {
        setSceneRect( mCenterItem->boundingRect() );
        mCenterItem->setPos( 0, 0 );
    }
    else
    {
        // Center in item coordinates
        QPointF currentItemCenter = mCenterItem->mapFromScene( mapToScene( viewport()->rect() ).boundingRect().center() );

        // Resize sceneRect
        auto vr = viewport()->rect();
        int vw = vr.width() / Scale() * 0.75;
        int vh = vr.height() / Scale() * 0.75;
        auto ir = mCenterItem->boundingRect();
        int iw = ir.width();
        int ih = ir.height();
        setSceneRect( 0, 0, iw + vw * 2, ih + vh * 2 );

        QPointF itemPos( vw, vh );
        mCenterItem->setPos( itemPos );

        QPointF newCenter = itemPos + currentItemCenter;
        centerOn( newCenter );
    }
}


//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- GUI


void
cViewDisplay2D::Init()
{
    mScroller = QScroller::scroller( this->viewport() );
    mTimer = new QTimer( this );
    mLensCursor = new QCursor( QPixmap( "resources/media/img/cursors/lens.png" ), 6, 6 );

    mScene = new QGraphicsScene();
}


void
cViewDisplay2D::Build()
{
    tSuperClass::setScene( mScene );
    setMouseTracking( true );

    QScrollerProperties ScrollerProperties = mScroller->scrollerProperties();
    QVariant OvershootPolicyOff = QVariant::fromValue< QScrollerProperties::OvershootPolicy >( QScrollerProperties::OvershootAlwaysOff );
    QVariant OvershootPolicyOn  = QVariant::fromValue< QScrollerProperties::OvershootPolicy >( QScrollerProperties::OvershootAlwaysOn );
    ScrollerProperties.setScrollMetric( QScrollerProperties::VerticalOvershootPolicy,       OvershootPolicyOff );
    ScrollerProperties.setScrollMetric( QScrollerProperties::HorizontalOvershootPolicy,     OvershootPolicyOff );
    ScrollerProperties.setScrollMetric( QScrollerProperties::ScrollingCurve,                QEasingCurve::OutCubic );
    mScroller->setScrollerProperties( ScrollerProperties );

    float fps = 60.f;
    int mstime = int( 1000.f / 60.f );
    mTimer->setInterval( mstime );
    QObject::connect( mTimer, SIGNAL( timeout() ), this, SLOT( tickSlot() ) );
    mTimer->start();
}


void
cViewDisplay2D::Compose()
{
    RecomputeSceneRectOnChange();
}


void
cViewDisplay2D::Destroy()
{
    delete  mLensCursor;
    delete  mTimer;

    delete  mScene;
}

