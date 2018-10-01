/*************************************************************************
*
*   Lavabo
*__________________
*
* EulerAngle.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "EulerAngle.h"


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


cEulerAngle::~cEulerAngle()
{
}


cEulerAngle::cEulerAngle() :
    mValue( 0.f ),
    mAxis( kIntrinsicX )
{
}


cEulerAngle::cEulerAngle( eAxis iAxis, float iValue ) :
    mValue( iValue ),
    mAxis( iAxis )
{
}


cEulerAngle::cEulerAngle( const  cEulerAngle  &iOther ) :
    mValue( iOther.mValue ),
    mAxis( iOther.mAxis )
{
}


cEulerAngle&
cEulerAngle::operator=( const cEulerAngle&  iOther )
{
    mValue = iOther.mValue;
    mAxis = iOther.mAxis;
    return  *this;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------ Get / Set


void
cEulerAngle::SetValue( float iValue )
{
    mValue = iValue;
}


void
cEulerAngle::SetAxis( eAxis iAxis )
{
    mAxis = iAxis;
}


float
cEulerAngle::Value()  const
{
    return  mValue;
}


cEulerAngle::eAxis
cEulerAngle::Axis()  const
{
    return  mAxis;
}

