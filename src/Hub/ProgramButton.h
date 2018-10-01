/*************************************************************************
*
*   Lavabo
*__________________
*
* ProgramButton.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


#include <QWidget>
#include <QLabel>
#include <QPixmap>


class cProgramButton :
    public QWidget
{
    Q_OBJECT

    typedef QWidget         tSuperClass;
    typedef cProgramButton  tSelf;

public:
    // Construction / Destruction
    virtual  ~cProgramButton();
    cProgramButton( const QString& iKey, QWidget*  parent = NULL );

protected:
    // Event
    virtual  void  resizeEvent( QResizeEvent*  event )  override;
    virtual  void  mouseDoubleClickEvent( QMouseEvent*  event )  override;

public slots:signals:
    void  DoubleClicked( QString );

private:
    // GUI utilities
    void  Init();
    void  Build();
    void  Compose();
    void  Destroy();

private:
    // Private Data Members
    QString mKey;
    QLabel* mImageLabel;
    QPixmap* mImage;
    QLabel* mTextLabel;
    QWidget* mOverlay;
};

