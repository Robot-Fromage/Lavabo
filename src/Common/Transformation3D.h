/*************************************************************************
*
*   Lavabo
*__________________
*
* Transformation3D.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


#include "EulerSet.h"


#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>


class cTransformation3D
{
public:
    // Construction / Destruction
    ~cTransformation3D();
    cTransformation3D();
    cTransformation3D( const  cTransformation3D&  iOther );
    cTransformation3D& operator=( const  cTransformation3D&  iOther );

public:
    // Pivot setter
    void  ResetPivot();
    void  SetPivot( const  glm::vec3& iValues );
    void  SetPivot( float iX, float iY, float iZ );
    void  SetPivotX( float iValue );
    void  SetPivotY( float iValue );
    void  SetPivotZ( float iValue );

    void  MovePivot( const  glm::vec3& iDelta );
    void  MovePivot( float iDeltaX, float iDeltaY, float iDeltaZ );
    void  MovePivotX( float iDelta );
    void  MovePivotY( float iDelta );
    void  MovePivotZ( float iDelta );
    void  MovePivotRight( float iDelta );
    void  MovePivotUp( float iDelta );
    void  MovePivotForward( float iDelta );

    // Translation setter
    void  ResetTranslation();
    void  SetTranslation( const  glm::vec3& iValues );
    void  SetTranslation( float iX, float iY, float iZ );
    void  SetTranslationX( float iValue );
    void  SetTranslationY( float iValue );
    void  SetTranslationZ( float iValue );

    void  Translate( const  glm::vec3& iDelta );
    void  Translate( float iDeltaX, float iDeltaY, float iDeltaZ );
    void  TranslateX( float iDelta );
    void  TranslateY( float iDelta );
    void  TranslateZ( float iDelta );
    void  TranslateRight( float iDelta );
    void  TranslateUp( float iDelta );
    void  TranslateForward( float iDelta );

    // Rotation setter
    void  ResetRotation();
    void  SetRotation( float iAngleRad, const  glm::vec3& iAxis );
    void  SetRotation( float iAngleRad, float iAxisX, float iAxisY, float iAxisZ );
    void  SetRotation( const  cEulerSet& iEulerSet );

    void  SetRotationX( float iValue );
    void  SetRotationY( float iValue );
    void  SetRotationZ( float iValue );
    void  SetYaw( float iValue );
    void  SetPitch( float iValue );
    void  SetRoll( float iValue );
    void  SetPrecession( float iValue );
    void  SetNutation( float iValue );

    void  Rotate( float iAngleRad, const  glm::vec3& iAxis );
    void  Rotate( float iAngleRad, float iAxisX, float iAxisY, float iAxisZ );
    void  Rotate( const  cEulerSet& iEulerSet );

    void  RotateX( float iValue );
    void  RotateY( float iValue );
    void  RotateZ( float iValue );
    void  DeltaYaw( float iValue );
    void  DeltaPitch( float iValue );
    void  DeltaRoll( float iValue );
    void  Precess( float iValue );
    void  Nutate( float iValue );

    // Scale setter
    void  ResetScale();
    void  SetScale( const  glm::vec3& iValues );
    void  SetScale( float iX, float iY, float iZ );
    void  SetScaleX( float iValue );
    void  SetScaleY( float iValue );
    void  SetScaleZ( float iValue );

    void  Stretch( const  glm::vec3& iValues );
    void  Stretch( float iX, float iY, float iZ );
    void  StretchX( float iValue );
    void  StretchY( float iValue );
    void  StretchZ( float iValue );

    void  DeltaScale( const  glm::vec3& iValues );
    void  DeltaScale( float iX, float iY, float iZ );
    void  DeltaScaleX( float iValue );
    void  DeltaScaleY( float iValue );
    void  DeltaScaleZ( float iValue );

public:
    // Pivot Getter
    glm::vec3  Pivot()  const;
    float  PivotX()  const;
    float  PivotY()  const;
    float  PivotZ()  const;

    // Translation Getter
    glm::vec3  Translation()  const;
    float  TranslationX()  const;
    float  TranslationY()  const;
    float  TranslationZ()  const;

    // Rotation Getter
    void  RotationAsAxisAngle( float* oAngle, glm::vec3* oAxis )  const;
    bool  RotationAsEulerSet( cEulerSet* ioEulerSet )  const;

    // Scale Getter
    glm::vec3  Scale()  const;
    float  ScaleX()  const;
    float  ScaleY()  const;
    float  ScaleZ()  const;

public:
    // Advanced Positioning
    void  TargetLocal( const  glm::vec3& iTarget ); // From Local
    void  TargetWorld( const  glm::vec3& iTarget ); // From World
    void  Target( const  glm::vec3& iTarget ); // From Parent

public:
    // Referential API
    glm::vec3  Right()  const;
    glm::vec3  Up()  const;
    glm::vec3  Forward()  const;
    glm::vec3  IntrinsicXAxis()  const; // Same as X( 1, 0, 0 ), expressed in local basis
    glm::vec3  IntrinsicYAxis()  const; // Same as Y( 0, 1, 0 ), expressed in local basis
    glm::vec3  IntrinsicZAxis()  const; // Same as Z( 0, 0, 1 ), expressed in local basis
    glm::vec3  ExtrinsicXAxis()  const; // Same as Right, expressed in local basis
    glm::vec3  ExtrinsicYAxis()  const; // Same as Up, expressed in local basis
    glm::vec3  ExtrinsicZAxis()  const; // Same as Forward, expressed in local basis
    glm::vec3  VectorForAxis( cEulerAngle::eAxis )  const;

public:
    // Parenting API
    void  SetParent( cTransformation3D* iParent );
    const  cTransformation3D* Parent( cTransformation3D* iParent )  const;
    void  AddChild( cTransformation3D* iParent );
    void  AddChildren( const  std::vector< cTransformation3D* >& iChildren );
    const  std::vector< cTransformation3D* >& Children()  const;

public:
    // Conversion API
    glm::vec4  ToWorld(     const  glm::vec4& iPoint )  const; // from world to local
    glm::vec4  FromWorld(   const  glm::vec4& iPoint )  const; // from local to world
    glm::vec4  ToParent(    const  glm::vec4& iPoint )  const; // from external to local
    glm::vec4  FromParent(  const  glm::vec4& iPoint )  const; // from local to external

    glm::vec3  PointToWorld(    const  glm::vec3& iPoint )  const; // from world to local
    glm::vec3  PointFromWorld(  const  glm::vec3& iPoint )  const; // from local to world
    glm::vec3  PointToParent(   const  glm::vec3& iPoint )  const; // from external to local
    glm::vec3  PointFromParent( const  glm::vec3& iPoint )  const; // from local to external

    glm::vec3  VecToWorld(      const  glm::vec3& iVec )  const; // from world to local
    glm::vec3  VecFromWorld(    const  glm::vec3& iVec )  const; // from local to world
    glm::vec3  VecToParent(     const  glm::vec3& iVec )  const; // from external to local
    glm::vec3  VecFromParent(   const  glm::vec3& iVec )  const; // from local to external

public:
    // Intermediate Matrix API
    glm::mat4 PivotMatrix()                 const;
    glm::mat4 InversePivotMatrix()          const;
    glm::mat4 TranslationMatrix()           const;
    glm::mat4 InverseTranslationMatrix()    const;
    glm::mat4 RotationMatrix()              const;
    glm::mat4 InverseRotationMatrix()       const;
    glm::mat4 ScaleMatrix()                 const;
    glm::mat4 InverseScaleMatrix()          const;

public:
    // Transformation Matrix API
    glm::mat4 Matrix()                      const;
    glm::mat4 InverseMatrix()               const;


public:
    // Public Matrix Cache Management
    void  UpdateMatrix()                    const;
    void  UpdateInverseMatrix()             const;

private:
    // Private Matrix Cache Management
    void  InvalidMatrix()                   const;

private:
    // Private Data Members
    glm::vec3 mPivot;
    glm::vec3 mTranslation;
    glm::vec3 mScale;
    glm::quat mRotation;

    mutable glm::mat4 mCachedMatrix;
    mutable glm::mat4 mCachedInverseMatrix;
    mutable bool mMatrixInvalid;
    mutable bool mInverseMatrixInvalid;

    cTransformation3D* mParent;
    std::vector< cTransformation3D* > mChildren;
};

