/*************************************************************************
*
*   Lavabo
*__________________
*
* EulerSet.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "EulerSet.h"


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


cEulerSet::~cEulerSet()
{
}


cEulerSet::cEulerSet()
{
    SetAxesValues( eSet::kInstrinsicXYZ, 0.f, 0.f, 0.f );
}


cEulerSet::cEulerSet( eSet iSet )
{
    SetAxesValues( iSet, 0.f, 0.f, 0.f );
}


cEulerSet::cEulerSet( eSet iSet, glm::vec3 iValues )
{
    SetAxesValues( iSet, iValues );
}


cEulerSet::cEulerSet( eSet iSet, float iPhiValue, float iThetaValue, float iPsiValue )
{
    SetAxesValues( iSet, iPhiValue, iThetaValue, iPsiValue );
}


cEulerSet::cEulerSet( cEulerAngle::eAxis iAxisPhi, float iValuePhi, cEulerAngle::eAxis iAxisTheta, float iValueTheta, cEulerAngle::eAxis iAxisPsi, float iValuePsi )
{
    SetAxesValues( iAxisPhi, iValuePhi, iAxisTheta, iValueTheta, iAxisPsi, iValuePsi );
}


cEulerSet::cEulerSet( const  cEulerAngle&  iPhi, const  cEulerAngle&  iTheta, const  cEulerAngle&  iPsi )
{
    SetEulerAngles( iPhi, iTheta, iPsi );
}


cEulerSet::cEulerSet( const  cEulerSet&  iOther )
{
    SetFrom( iOther );
}


cEulerSet&
cEulerSet::operator=( const  cEulerSet&  iOther )
{
    SetFrom( iOther );
    return  *this;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------ Get / Set


void
cEulerSet::SetFrom( const  cEulerSet& iOther )
{
    mPhi = iOther.mPhi;
    mTheta = iOther.mTheta;
    mPsi = iOther.mPsi;
}


void
cEulerSet::SetEulerAngles( const  cEulerAngle& iPhi, const  cEulerAngle& iTheta, const  cEulerAngle& iPsi )
{
    mPhi = iPhi;
    mTheta = iTheta;
    mPsi = iPsi;
}


void
cEulerSet::SetAxes( eSet iSet )
{
    switch( iSet )
    {
        case eSet::kInstrinsicXYZ:
        case eSet::kYawPitchRoll:
        case eSet::kAeronautic:
        {
            SetAxes( cEulerAngle::eAxis::kIntrinsicX, cEulerAngle::eAxis::kIntrinsicY, cEulerAngle::eAxis::kIntrinsicZ );
            break;
        }
        case eSet::kExtrinsicXYZ:
        {
            SetAxes( cEulerAngle::eAxis::kExtrinsicX, cEulerAngle::eAxis::kExtrinsicY, cEulerAngle::eAxis::kExtrinsicZ );
            break;
        }
        case eSet::kPrecessionNutationIntrinsicRotation:
        case eSet::kAstronomic:
        {
            SetAxes( cEulerAngle::eAxis::kExtrinsicX, cEulerAngle::eAxis::kExtrinsicY, cEulerAngle::eAxis::kIntrinsicZ );
            break;
        }
    }
}


void
cEulerSet::SetAxes( cEulerAngle::eAxis iAxisPhi, cEulerAngle::eAxis iAxisTheta, cEulerAngle::eAxis iAxisPsi )
{
    mPhi.SetAxis( iAxisPhi );
    mTheta.SetAxis( iAxisTheta );
    mPsi.SetAxis( iAxisPsi );
}


void
cEulerSet::SetAxesValues( eSet iSet, glm::vec3 iValues )
{
    SetAxes( iSet );
    SetValues( iValues );
}


void
cEulerSet::SetAxesValues( eSet iSet, float iValuePhi, float iValueTheta, float iValuePsi )
{
    SetAxes( iSet );
    SetValues( iValuePhi, iValueTheta, iValuePsi );
}


void
cEulerSet::SetAxesValues( cEulerAngle::eAxis iAxisPhi, float iValuePhi, cEulerAngle::eAxis iAxisTheta, float iValueTheta, cEulerAngle::eAxis iAxisPsi, float iValuePsi )
{
    SetAxes( iAxisPhi, iAxisTheta, iAxisPsi );
    SetValues( iValuePhi, iValueTheta, iValuePsi );
}


void
cEulerSet::SetValues( glm::vec3 iValues )
{
    SetValues( iValues.x, iValues.y, iValues.z );
}


void
cEulerSet::SetValues( float iValuePhi, float iValueTheta, float iValuePsi )
{
    mPhi.SetValue( iValuePhi );
    mTheta.SetValue( iValueTheta );
    mPsi.SetValue( iValuePsi );
}


void
cEulerSet::SetPhi( const  cEulerAngle&  iValue )
{
    mPhi = iValue;
}


void
cEulerSet::SetTheta( const  cEulerAngle&  iValue )
{
    mTheta = iValue;
}


void
cEulerSet::SetPsi( const  cEulerAngle&  iValue )
{
    mPsi = iValue;
}


void
cEulerSet::SetPhiValue( float iValue )
{
    mPhi.SetValue( iValue );
}


void
cEulerSet::SetThetaValue( float iValue )
{
    mTheta.SetValue( iValue );
}


void
cEulerSet::SetPsiValue( float iValue )
{
    mPsi.SetValue( iValue );
}


void
cEulerSet::SetPhiAxis( cEulerAngle::eAxis  iAxis )
{
    mPhi.SetAxis( iAxis );
}


void
cEulerSet::SetThetaAxis( cEulerAngle::eAxis  iAxis )
{
    mTheta.SetAxis( iAxis );
}


void
cEulerSet::SetPsiAxis( cEulerAngle::eAxis  iAxis )
{
    mPsi.SetAxis( iAxis );
}


const  cEulerAngle&
cEulerSet::Phi()
{
    return  mPhi;
}


const  cEulerAngle&
cEulerSet::Phi()  const
{
    return  mPhi;
}
const  cEulerAngle&
cEulerSet::Theta()
{
    return  mTheta;
}


const  cEulerAngle&
cEulerSet::Theta()  const
{
    return  mTheta;
}


const  cEulerAngle&
cEulerSet::Psi()
{
    return  mPsi;
}


const  cEulerAngle&
cEulerSet::Psi()  const
{
    return  mPsi;
}


float
cEulerSet::PhiValue()  const
{
    return  mPhi.Value();
}


float
cEulerSet::ThetaValue()  const
{
    return  mTheta.Value();
}


float
cEulerSet::PsiValue()  const
{
    return  mPsi.Value();
}


cEulerAngle::eAxis
cEulerSet::PhiAxis()  const
{
    return  mPhi.Axis();
}


cEulerAngle::eAxis
cEulerSet::ThetaAxis()  const
{
    return  mTheta.Axis();
}


cEulerAngle::eAxis
cEulerSet::PsiAxis()  const
{
    return  mPsi.Axis();
}

