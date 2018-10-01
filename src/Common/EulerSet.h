/*************************************************************************
*
*   Lavabo
*__________________
*
* EulerSet.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


#include "EulerAngle.h"


#include <glm/vec3.hpp>


class cEulerSet
{

public:
    enum  eSet
    {
        kInstrinsicXYZ,
        kExtrinsicXYZ,
        kYawPitchRoll,
        kPrecessionNutationIntrinsicRotation,
        kAeronautic,
        kAstronomic,
    };

public:
    // Construction / Destruction
    ~cEulerSet();
    cEulerSet();
    cEulerSet( eSet iSet );
    cEulerSet( eSet iSet, glm::vec3 iValues );
    cEulerSet( eSet iSet, float iPhiValue, float iThetaValue, float iPsiValue );
    cEulerSet( cEulerAngle::eAxis iAxisPhi, float iValuePhi, cEulerAngle::eAxis iAxisTheta, float iValueTheta, cEulerAngle::eAxis iAxisPsi, float iValuePsi );
    cEulerSet( const  cEulerAngle&  iPhi, const  cEulerAngle&  iTheta, const  cEulerAngle&  iPsi );
    cEulerSet( const  cEulerSet&  iOther );
    cEulerSet& operator=( const  cEulerSet&  iOther );

public:
    // Get / Set
    void  SetFrom( const  cEulerSet& iOther );
    void  SetEulerAngles( const  cEulerAngle& iPhi, const  cEulerAngle& iTheta, const  cEulerAngle& iPsi );
    void  SetAxes( eSet iSet );
    void  SetAxes( cEulerAngle::eAxis iAxisPhi, cEulerAngle::eAxis iAxisTheta, cEulerAngle::eAxis iAxisPsi );
    void  SetAxesValues( eSet iSet, glm::vec3 iValues );
    void  SetAxesValues( eSet iSet, float iValuePhi, float iValueTheta, float iValuePsi );
    void  SetAxesValues( cEulerAngle::eAxis iAxisPhi, float iValuePhi, cEulerAngle::eAxis iAxisTheta, float iValueTheta, cEulerAngle::eAxis iAxisPsi, float iValuePsi );
    void  SetValues( glm::vec3 iValues );
    void  SetValues( float iValuePhi, float iValueTheta, float iValuePsi );

    void  SetPhi( const  cEulerAngle&  iValue );
    void  SetTheta( const  cEulerAngle&  iValue );
    void  SetPsi( const  cEulerAngle&  iValue );

    void  SetPhiValue( float iValue );
    void  SetThetaValue( float iValue );
    void  SetPsiValue( float iValue );

    void  SetPhiAxis( cEulerAngle::eAxis  iAxis );
    void  SetThetaAxis( cEulerAngle::eAxis  iAxis );
    void  SetPsiAxis( cEulerAngle::eAxis  iAxis );

    const  cEulerAngle&  Phi();
    const  cEulerAngle&  Phi()  const;
    const  cEulerAngle&  Theta();
    const  cEulerAngle&  Theta()  const;
    const  cEulerAngle&  Psi();
    const  cEulerAngle&  Psi()  const;
    float  PhiValue()  const;
    float  ThetaValue()  const;
    float  PsiValue()  const;
    cEulerAngle::eAxis  PhiAxis()  const;
    cEulerAngle::eAxis  ThetaAxis()  const;
    cEulerAngle::eAxis  PsiAxis()  const;

private:
    // Data Members
    cEulerAngle mPhi;
    cEulerAngle mTheta;
    cEulerAngle mPsi;
};

