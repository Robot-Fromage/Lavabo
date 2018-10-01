/*************************************************************************
*
*   Lavabo
*__________________
*
* EulerAngle.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


class cEulerAngle
{

public:
    enum  eAxis
    {
        kIntrinsicX,
        kIntrinsicY,
        kIntrinsicZ,
        kExtrinsicX,
        kExtrinsicY,
        kExtrinsicZ,
    };

public:
    // Construction / Destruction
    ~cEulerAngle();
    cEulerAngle();
    cEulerAngle( eAxis iAxis, float iValue );
    cEulerAngle( const  cEulerAngle&  iOther );
    cEulerAngle& operator=( const  cEulerAngle&  iOther );

public:
    // Get / Set
    void  SetValue( float iValue );
    void  SetAxis( eAxis iAxis );

    float Value()  const;
    eAxis Axis()  const;

private:
    // Data Members
    float  mValue; // rad
    eAxis  mAxis;
};

