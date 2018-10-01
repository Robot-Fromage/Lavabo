/*************************************************************************
*
*   Lavabo
*__________________
*
* Transformation3D.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "Transformation3D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction

/*
cTransformation3D::~cTransformation3D()
{
}


cTransformation3D::cTransformation3D()
{
}


cTransformation3D::cTransformation3D( const  cTransformation3D&  iOther )
{
    *this = iOther;
}


cTransformation3D&
cTransformation3D::operator=( const  cTransformation3D&  iOther )
{
    mPivot = iOther.mPivot;
    mTranslation = iOther.mTranslation;
    mScale = iOther.mScale;
    mRotation = iOther.mRotation;
    mCachedMatrix = iOther.mCachedMatrix;
    mCachedInverseMatrix = iOther.mCachedInverseMatrix;
    mMatrixInvalid = iOther.mMatrixInvalid;
    mInverseMatrixInvalid = iOther.mInverseMatrixInvalid;

    // We do not copy parenting relationships
    mParent = NULL;
    mChildren.clear();

    return  *this;
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------- Pivot setter


void
cTransformation3D::ResetPivot()
{
    mPivot = glm::vec3();
    InvalidMatrix();
}


void
cTransformation3D::SetPivot( const  glm::vec3& iValues )
{
    mPivot = iValues;
    InvalidMatrix();
}


void
cTransformation3D::SetPivot( float iX, float iY, float iZ )
{
    mPivot = glm::vec3( iX, iY, iZ );
    InvalidMatrix();
}


void
cTransformation3D::SetPivotX( float iValue )
{
    mPivot.x = iValue;
    InvalidMatrix();
}


void
cTransformation3D::SetPivotY( float iValue )
{
    mPivot.y = iValue;
    InvalidMatrix();
}


void
cTransformation3D::SetPivotZ( float iValue )
{
    mPivot.z = iValue;
    InvalidMatrix();
}


void
cTransformation3D::MovePivot( const  glm::vec3& iDelta )
{
    mPivot += iDelta;
    InvalidMatrix();
}


void
cTransformation3D::MovePivot( float iDeltaX, float iDeltaY, float iDeltaZ )
{
    mPivot += glm::vec3( iDeltaX, iDeltaY, iDeltaZ );
    InvalidMatrix();
}


void
cTransformation3D::MovePivotX( float iDelta )
{
    mPivot.x += iDelta;
    InvalidMatrix();
}


void
cTransformation3D::MovePivotY( float iDelta )
{
    mPivot.y += iDelta;
    InvalidMatrix();
}


void
cTransformation3D::MovePivotZ( float iDelta )
{
    mPivot.z += iDelta;
    InvalidMatrix();
}


void
cTransformation3D::MovePivotRight( float iDelta )
{
    mPivot += Right() * iDelta;
    InvalidMatrix();
}


void
cTransformation3D::MovePivotUp( float iDelta )
{
    mPivot += Up() * iDelta;
    InvalidMatrix();
}


void
cTransformation3D::MovePivotForward( float iDelta )
{
    mPivot += Forward() * iDelta;
    InvalidMatrix();
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Translation setter


void
cTransformation3D::ResetTranslation()
{
    mTranslation = glm::vec3();
    InvalidMatrix();
}


void
cTransformation3D::SetTranslation( const  glm::vec3& iValues )
{
    mTranslation = iValues;
    InvalidMatrix();
}


void
cTransformation3D::SetTranslation( float iX, float iY, float iZ )
{
    mTranslation = glm::vec3( iX, iY, iZ );
    InvalidMatrix();
}


void
cTransformation3D::SetTranslationX( float iValue )
{
    mTranslation.x = iValue;
    InvalidMatrix();
}


void
cTransformation3D::SetTranslationY( float iValue )
{
    mTranslation.y = iValue;
    InvalidMatrix();
}


void
cTransformation3D::SetTranslationZ( float iValue )
{
    mTranslation.z = iValue;
    InvalidMatrix();
}


void
cTransformation3D::Translate( const  glm::vec3& iDelta )
{
    mTranslation += iDelta;
    InvalidMatrix();
}


void
cTransformation3D::Translate( float iDeltaX, float iDeltaY, float iDeltaZ )
{
    mTranslation += glm::vec3( iDeltaX, iDeltaY, iDeltaZ );
    InvalidMatrix();
}


void
cTransformation3D::TranslateX( float iDelta )
{
    mTranslation.x += iDelta;
    InvalidMatrix();
}


void
cTransformation3D::TranslateY( float iDelta )
{
    mTranslation.y += iDelta;
    InvalidMatrix();
}


void
cTransformation3D::TranslateZ( float iDelta )
{
    mTranslation.z += iDelta;
    InvalidMatrix();
}


void
cTransformation3D::TranslateRight( float iDelta )
{
    mTranslation += Right() * iDelta;
    InvalidMatrix();
}


void
cTransformation3D::TranslateUp( float iDelta )
{
    mTranslation += Up() * iDelta;
    InvalidMatrix();
}


void
cTransformation3D::TranslateForward( float iDelta )
{
    mTranslation += Forward() * iDelta;
    InvalidMatrix();
}


//----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------  Rotation setter


void
cTransformation3D::ResetRotation()
{
    mRotation = glm::quat();
    InvalidMatrix();
}


void
cTransformation3D::SetRotation( float iAngleRad, const  glm::vec3& iAxis )
{
    mRotation = glm::quat( iAngleRad, iAxis );
    InvalidMatrix();
}


void
cTransformation3D::SetRotation( float iAngleRad, float iAxisX, float iAxisY, float iAxisZ )
{
    mRotation = glm::quat( iAngleRad, iAxisX, iAxisY, iAxisZ );
    InvalidMatrix();
}


void
cTransformation3D::SetRotation( const  cEulerSet& iEulerSet )
{
    ResetRotation();
    Rotate( iEulerSet );
}


void
cTransformation3D::SetRotationX( float iValue )
{
    ResetRotation();
    RotateX( iValue );
}


void
cTransformation3D::SetRotationY( float iValue )
{
    ResetRotation();
    RotateX( iValue );
}


void
cTransformation3D::SetRotationZ( float iValue )
{
    ResetRotation();
    RotateZ( iValue );
}


void
cTransformation3D::SetYaw( float iValue )
{
    ResetRotation();
    DeltaYaw( iValue );
}


void
cTransformation3D::SetPitch( float iValue )
{
    ResetRotation();
    DeltaPitch( iValue );
}


void
cTransformation3D::SetRoll( float iValue )
{
    ResetRotation();
    DeltaRoll( iValue );
}


void
cTransformation3D::SetPrecession( float iValue )
{
    ResetRotation();
    Precess( iValue );
}


void
cTransformation3D::SetNutation( float iValue )
{
    ResetRotation();
    Nutate( iValue );
}


void
cTransformation3D::Rotate( float iAngleRad, const  glm::vec3& iAxis )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iAngleRad, iAxis );
    InvalidMatrix();
}


void
cTransformation3D::Rotate( float iAngleRad, float iAxisX, float iAxisY, float iAxisZ )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iAngleRad, glm::vec3( iAxisX, iAxisY, iAxisZ ) );
    InvalidMatrix();
}


void
cTransformation3D::Rotate( const  cEulerSet& iEulerSet )
{
    const  cEulerAngle&  phi = iEulerSet.Phi();
    const  cEulerAngle&  theta = iEulerSet.Theta();
    const  cEulerAngle&  psi = iEulerSet.Psi();
    glm::vec3  phiAxisVector    = VectorForAxis( phi.Axis() );
    glm::vec3  thetaAxisVector  = VectorForAxis( theta.Axis() );
    glm::vec3  psiAxisVector    = VectorForAxis( psi.Axis() );
    float  phiValue     = phi.Value();
    float  thetaValue   = theta.Value();
    float  psiValue     = psi.Value();
    Rotate( phiValue, phiAxisVector );
    Rotate( thetaValue, thetaAxisVector );
    Rotate( psiValue, psiAxisVector );
}


void
cTransformation3D::RotateX( float iValue )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iValue, ExtrinsicXAxis() );
    InvalidMatrix();
}


void
cTransformation3D::RotateY( float iValue )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iValue, ExtrinsicYAxis() );
    InvalidMatrix();
}


void
cTransformation3D::RotateZ( float iValue )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iValue, ExtrinsicZAxis() );
    InvalidMatrix();
}


void
cTransformation3D::DeltaYaw( float iValue )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iValue, Up() );
    InvalidMatrix();
}


void
cTransformation3D::DeltaPitch( float iValue )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iValue, Right() );
    InvalidMatrix();
}


void
cTransformation3D::DeltaRoll( float iValue )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iValue, Forward() );
    InvalidMatrix();
}


void
cTransformation3D::Precess( float iValue )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iValue, ExtrinsicYAxis() );
    InvalidMatrix();
}


void
cTransformation3D::Nutate( float iValue )
{
    mRotationMatrix = glm::rotate( mRotationMatrix, iValue, IntrinsicXAxis() );
    InvalidMatrix();
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------- Scale setter


void
cTransformation3D::ResetScale()
{
    // Reset to identity matrix.
    // glm::mat4() gives:
    // mat4
    // 1 0 0 0
    // 0 1 0 0
    // 0 0 1 0
    // 0 0 0 1
    // ( see constructor implementation if confirmation needed. )

    mScaleMatrix = glm::mat4();
    InvalidMatrix();
}


void
cTransformation3D::SetScale( const  glm::vec3& iValues )
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                 [x • 0]  x | 0   x | 0   x | 0
    //                  y | 1  [y • 1]  y | 1   y | 1
    //                  z | 2   z | 2  [z • 2]  z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1

    mTranslationMatrix[0].x = iValues.x;
    mTranslationMatrix[1].y = iValues.y;
    mTranslationMatrix[2].z = iValues.z;
    InvalidMatrix();
}


void
cTransformation3D::SetScale( float iX, float iY, float iZ )
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                 [x • 0]  x | 0   x | 0   x | 0
    //                  y | 1  [y • 1]  y | 1   y | 1
    //                  z | 2   z | 2  [z • 2]  z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1

    mTranslationMatrix[0].x = iX;
    mTranslationMatrix[1].y = iY;
    mTranslationMatrix[2].z = iZ;
    InvalidMatrix();
}


void
cTransformation3D::SetScaleX( float iValue )
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                 [x • 0]  x | 0   x | 0   x | 0
    //                  y | 1   y | 1   y | 1   y | 1
    //                  z | 2   z | 2   z | 2   z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1

    mTranslationMatrix[0].x = iValue;
    InvalidMatrix();
}


void
cTransformation3D::SetScaleY( float iValue )
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                  x | 0   x | 0   x | 0   x | 0
    //                  y | 1  [y • 1]  y | 1   y | 1
    //                  z | 2   z | 2   z | 2   z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1

    mTranslationMatrix[1].y = iValue;
    InvalidMatrix();
}


void
cTransformation3D::SetScaleZ( float iValue )
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                  x | 0   x | 0   x | 0   x | 0
    //                  y | 1   y | 1   y | 1   y | 1
    //                  z | 2   z | 2  [z • 2]  z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1

    mTranslationMatrix[2].z = iValue;
    InvalidMatrix();
}


void
cTransformation3D::Stretch( const  glm::vec3& iValues )
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                 [x • 0]  x | 0   x | 0   x | 0
    //                  y | 1  [y • 1]  y | 1   y | 1
    //                  z | 2   z | 2  [z • 2]  z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1

    mTranslationMatrix[0].x *= iValues.x;
    mTranslationMatrix[1].y *= iValues.y;
    mTranslationMatrix[2].z *= iValues.z;
    InvalidMatrix();
}


void
cTransformation3D::Stretch( float iX, float iY, float iZ )
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                 [x • 0]  x | 0   x | 0   x | 0
    //                  y | 1  [y • 1]  y | 1   y | 1
    //                  z | 2   z | 2  [z • 2]  z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1

    mTranslationMatrix[0].x *= iX;
    mTranslationMatrix[1].y *= iY;
    mTranslationMatrix[2].z *= iZ;
    InvalidMatrix();
}


void
cTransformation3D::StretchX( float iValue )
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                 [x • 0]  x | 0   x | 0   x | 0
    //                  y | 1   y | 1   y | 1   y | 1
    //                  z | 2   z | 2   z | 2   z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1

    mTranslationMatrix[0].x *= iValue;
    InvalidMatrix();
}


void
cTransformation3D::StretchY( float iValue )
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                  x | 0   x | 0   x | 0   x | 0
    //                  y | 1  [y • 1]  y | 1   y | 1
    //                  z | 2   z | 2   z | 2   z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1

    mTranslationMatrix[1].y *= iValue;
    InvalidMatrix();
}


void
cTransformation3D::StretchZ( float iValue )
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                  x | 0   x | 0   x | 0   x | 0
    //                  y | 1   y | 1   y | 1   y | 1
    //                  z | 2   z | 2  [z • 2]  z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1

    mTranslationMatrix[2].z *= iValue;
    InvalidMatrix();
}


void
cTransformation3D::DeltaScale( const  glm::vec3& iValues )
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                 [x • 0]  x | 0   x | 0   x | 0
    //                  y | 1  [y • 1]  y | 1   y | 1
    //                  z | 2   z | 2  [z • 2]  z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1

    mTranslationMatrix[0].x += iValues.x;
    mTranslationMatrix[1].y += iValues.y;
    mTranslationMatrix[2].z += iValues.z;
    InvalidMatrix();
}


void
cTransformation3D::DeltaScale( float iX, float iY, float iZ )
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                 [x • 0]  x | 0   x | 0   x | 0
    //                  y | 1  [y • 1]  y | 1   y | 1
    //                  z | 2   z | 2  [z • 2]  z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1

    mTranslationMatrix[0].x += iX;
    mTranslationMatrix[1].y += iY;
    mTranslationMatrix[2].z += iZ;
    InvalidMatrix();
}


void
cTransformation3D::DeltaScaleX( float iValue )
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                 [x • 0]  x | 0   x | 0   x | 0
    //                  y | 1   y | 1   y | 1   y | 1
    //                  z | 2   z | 2   z | 2   z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1

    mTranslationMatrix[0].x += iValue;
    InvalidMatrix();
}


void
cTransformation3D::DeltaScaleY( float iValue )
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                  x | 0   x | 0   x | 0   x | 0
    //                  y | 1  [y • 1]  y | 1   y | 1
    //                  z | 2   z | 2   z | 2   z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1

    mTranslationMatrix[1].y += iValue;
    InvalidMatrix();
}


void
cTransformation3D::DeltaScaleZ( float iValue )
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                  x | 0   x | 0   x | 0   x | 0
    //                  y | 1   y | 1   y | 1   y | 1
    //                  z | 2   z | 2  [z • 2]  z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1

    mTranslationMatrix[2].z += iValue;
    InvalidMatrix();
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------- Pivot Getter


glm::vec3
cTransformation3D::Pivot()  const
{
    // glm::mat4 is column-major order
    // mat4                                     •
    // 00 10 20 30                              .
    // 01 11 21 31  mat4                        .
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                  x | 0   x | 0   x | 0   x | 0   •
    //                  y | 1   y | 1   y | 1   y | 1   •
    //                  z | 2   z | 2   z | 2   z | 2   •
    //                  w | 3   w | 3   w | 3   w | 3

    // pivot acts as a translation matrix
    // 1 0 0 x
    // 0 1 0 y
    // 0 0 1 z
    // 0 0 0 1  This is the look of a column-major pure translation matrix

    // Notice the minus, Pivot corresponds to an inverted translation.
    return  -mPivotMatrix[3];
}


float
cTransformation3D::PivotX()  const
{
    // glm::mat4 is column-major order
    // mat4                                     •
    // 00 10 20 30                              .
    // 01 11 21 31  mat4                        .
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                  x | 0   x | 0   x | 0   x | 0   •
    //                  y | 1   y | 1   y | 1   y | 1
    //                  z | 2   z | 2   z | 2   z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // pivot acts as a translation matrix
    // 1 0 0 x
    // 0 1 0 y
    // 0 0 1 z
    // 0 0 0 1  This is the look of a column-major pure translation matrix

    // Notice the minus, Pivot corresponds to an inverted translation.
    return  -mPivotMatrix[3].x;
}


float
cTransformation3D::PivotY()  const
{
    // glm::mat4 is column-major order
    // mat4                                     •
    // 00 10 20 30                              .
    // 01 11 21 31  mat4                        .
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                  x | 0   x | 0   x | 0   x | 0
    //                  y | 1   y | 1   y | 1   y | 1   •
    //                  z | 2   z | 2   z | 2   z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // pivot acts as a translation matrix
    // 1 0 0 x
    // 0 1 0 y
    // 0 0 1 z
    // 0 0 0 1  This is the look of a column-major pure translation matrix

    // Notice the minus, Pivot corresponds to an inverted translation.
    return  -mPivotMatrix[3].y;
}


float
cTransformation3D::PivotZ()  const
{
    // glm::mat4 is column-major order
    // mat4                                     •
    // 00 10 20 30                              .
    // 01 11 21 31  mat4                        .
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                  x | 0   x | 0   x | 0   x | 0
    //                  y | 1   y | 1   y | 1   y | 1
    //                  z | 2   z | 2   z | 2   z | 2   •
    //                  w | 3   w | 3   w | 3   w | 3

    // pivot acts as a translation matrix
    // 1 0 0 x
    // 0 1 0 y
    // 0 0 1 z
    // 0 0 0 1  This is the look of a column-major pure translation matrix

    // Notice the minus, Pivot corresponds to an inverted translation.
    return  -mPivotMatrix[3].z;
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Translation Getter


glm::vec3
cTransformation3D::Translation()  const
{
    // glm::mat4 is column-major order
    // mat4                                     •
    // 00 10 20 30                              .
    // 01 11 21 31  mat4                        .
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                  x | 0   x | 0   x | 0   x | 0   •
    //                  y | 1   y | 1   y | 1   y | 1   •
    //                  z | 2   z | 2   z | 2   z | 2   •
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure translation matrix
    // 1 0 0 x
    // 0 1 0 y
    // 0 0 1 z
    // 0 0 0 1

    return  mPivotMatrix[3];
}


float
cTransformation3D::TranslationX()  const
{
    // glm::mat4 is column-major order
    // mat4                                     •
    // 00 10 20 30                              .
    // 01 11 21 31  mat4                        .
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                  x | 0   x | 0   x | 0   x | 0   •
    //                  y | 1   y | 1   y | 1   y | 1
    //                  z | 2   z | 2   z | 2   z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure translation matrix
    // 1 0 0 x
    // 0 1 0 y
    // 0 0 1 z
    // 0 0 0 1

    return  mPivotMatrix[3].x;
}


float
cTransformation3D::TranslationY()  const
{
    // glm::mat4 is column-major order
    // mat4                                     •
    // 00 10 20 30                              .
    // 01 11 21 31  mat4                        .
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                  x | 0   x | 0   x | 0   x | 0
    //                  y | 1   y | 1   y | 1   y | 1   •
    //                  z | 2   z | 2   z | 2   z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure translation matrix
    // 1 0 0 x
    // 0 1 0 y
    // 0 0 1 z
    // 0 0 0 1

    return  mPivotMatrix[3].y;
}


float
cTransformation3D::TranslationZ()  const
{
    // glm::mat4 is column-major order
    // mat4                                     •
    // 00 10 20 30                              .
    // 01 11 21 31  mat4                        .
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                  x | 0   x | 0   x | 0   x | 0
    //                  y | 1   y | 1   y | 1   y | 1
    //                  z | 2   z | 2   z | 2   z | 2   •
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure translation matrix
    // 1 0 0 x
    // 0 1 0 y
    // 0 0 1 z
    // 0 0 0 1

    return  mPivotMatrix[3].z;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Rotation Getter


void
cTransformation3D::RotationAsAxisAngle( float* oAngle, glm::vec3* oAxis )  const
{
    // link:[http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToAngle/index.htm]

    double angle,x,y,z; // variables for result
    double epsilon = 0.01; // margin to allow for rounding errors
    double epsilon2 = 0.1; // margin to distinguish between 0 and 180 degrees
    const glm::mat4& m = mRotationMatrix;

    // optional check that input is pure rotation, 'isRotationMatrix' is defined at:
    // https://www.euclideanspace.com/maths/algebra/matrix/orthogonal/rotation/
    // assert isRotationMatrix(m) : "not valid rotation matrix" ;// for debugging
    if(   ( abs( m[0][1] - m[1][0] ) < epsilon )
       && ( abs( m[0][2] - m[2][0] ) < epsilon )
       && ( abs( m[1][2] - m[2][1] ) < epsilon ) )
    {
        // singularity found
        // first check for identity matrix which must have +1 for all terms
        //  in leading diagonaland zero in other terms
        if (   ( abs( m[0][1] + m[1][0] ) < epsilon2 )
            && ( abs( m[0][2] + m[2][0] ) < epsilon2 )
            && ( abs( m[1][2] + m[2][1] ) < epsilon2 )
            && ( abs( m[0][0] + m[1][1] + m[2][2] - 3 ) < epsilon2 ) )
        {
            // this singularity is identity matrix so angle = 0
            // zero angle, arbitrary axis
            *oAxis = glm::vec3( 0, 1, 0 );
            *oAngle = 0.f;
            return;
        }

        // otherwise this singularity is angle = 180
        angle = 3.14159265359f;
        double xx = ( m[0][0] +1 ) / 2;
        double yy = ( m[1][1] +1 ) / 2;
        double zz = ( m[2][2] +1 ) / 2;
        double xy = ( m[0][1] + m[1][0] ) / 4;
        double xz = ( m[0][2] + m[2][0] ) / 4;
        double yz = ( m[1][2] + m[2][1] ) / 4;

        if( ( xx > yy ) && ( xx > zz ) ) // m[0][0] is the largest diagonal term
        {
            if( xx < epsilon )
            {
                x = 0;
                y = 0.7071;
                z = 0.7071;
            }
            else
            {
                x = sqrt(xx);
                y = xy/x;
                z = xz/x;
            }
        }
        else if(yy > zz) // m[1][1] is the largest diagonal term
        {
            if (yy< epsilon)
            {
                x = 0.7071;
                y = 0;
                z = 0.7071;
            }
            else
            {
                y = sqrt(yy);
                x = xy/y;
                z = yz/y;
            }
        }
        else // m[2][2] is the largest diagonal term so base result on this
        {
            if(zz< epsilon)
            {
                x = 0.7071;
                y = 0.7071;
                z = 0;
            }
            else
            {
                z = sqrt(zz);
                x = xz/z;
                y = yz/z;
            }
        }

        // return 180 deg rotation
        *oAxis = glm::vec3( x, y, z );
        *oAngle = angle;
        return;
    }
    // as we have reached here there are no singularities so we can handle normally
    double s = sqrt(  ( m[2][1] - m[1][2] ) * ( m[2][1] - m[1][2] )
                    + ( m[0][2] - m[2][0] ) * ( m[0][2] - m[2][0] )
                    + ( m[1][0] - m[0][1] ) * ( m[1][0] - m[0][1] ) ); // used to normalise
    if( abs(s) < 0.001) s=1;
        // prevent divide by zero, should not happen if matrix is orthogonal and should be
        // caught by singularity test above, but I've left it in just in case
    angle = acos( ( m[0][0] + m[1][1] + m[2][2] - 1 ) / 2 );
    x = ( m[2][1] - m[1][2] ) / s;
    y = ( m[0][2] - m[2][0] ) / s;
    z = ( m[1][0] - m[0][1] ) / s;

    *oAxis = glm::vec3( x, y, z );
    *oAngle = angle;
    return;
}


bool
cTransformation3D::RotationAsEulerSet( cEulerSet* ioEulerSet )  const
{
    // The function returns a boolean because in some case we cannot compute the rotation with the given set.
    // We use the input EulerSet to collect the axes
    auto phiAxis = ioEulerSet->PhiAxis();
    auto thetaAxis = ioEulerSet->ThetaAxis();
    auto psiAxis = ioEulerSet->PsiAxis();

    //TODO

    return  true;
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------- Scale Getter


glm::vec3
cTransformation3D::Scale()  const
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                 [x • 0]  x | 0   x | 0   x | 0
    //                  y | 1  [y • 1]  y | 1   y | 1
    //                  z | 2   z | 2  [z • 2]  z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1

    auto x = mTranslationMatrix[0].x;
    auto y = mTranslationMatrix[1].y;
    auto z = mTranslationMatrix[2].z;
    return  glm::vec3( x, y, z );
}


float
cTransformation3D::ScaleX()  const
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                 [x • 0]  x | 0   x | 0   x | 0
    //                  y | 1   y | 1   y | 1   y | 1
    //                  z | 2   z | 2   z | 2   z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1

    return  mTranslationMatrix[0].x;
}


float
cTransformation3D::ScaleY()  const
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                  x | 0   x | 0   x | 0   x | 0
    //                  y | 1  [y • 1]  y | 1   y | 1
    //                  z | 2   z | 2   z | 2   z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1

    return  mTranslationMatrix[1].y;
}


float
cTransformation3D::ScaleZ()  const
{
    // glm::mat4 is column-major order
    // mat4
    // 00 10 20 30
    // 01 11 21 31  mat4
    // 02 12 22 32      0       1       2       3
    // 03 13 23 33      vec4    vec4    vec4    vec4
    //                  x | 0   x | 0   x | 0   x | 0
    //                  y | 1   y | 1   y | 1   y | 1
    //                  z | 2   z | 2  [z • 2]  z | 2
    //                  w | 3   w | 3   w | 3   w | 3

    // This is the look of a column-major pure scale matrix
    // x 0 0 0
    // 0 y 0 0
    // 0 0 z 0
    // 0 0 0 1

    return  mTranslationMatrix[2].z;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------- Advanced Positioning


void
cTransformation3D::TargetLocal( const  glm::vec3& iTarget )
{
}


void
cTransformation3D::TargetWorld( const  glm::vec3& iTarget )
{
}


void
cTransformation3D::Target( const  glm::vec3& iTarget )
{
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Referential API


glm::vec3
cTransformation3D::Right()  const
{
    return  glm::vec3();
}


glm::vec3
cTransformation3D::Up()  const
{
    return  glm::vec3();
}


glm::vec3
cTransformation3D::Forward()  const
{
    return  glm::vec3();
}


glm::vec3
cTransformation3D::IntrinsicXAxis()  const
{
    return  glm::vec3();
}


glm::vec3
cTransformation3D::IntrinsicYAxis()  const
{
    return  glm::vec3();
}


glm::vec3
cTransformation3D::IntrinsicZAxis()  const
{
    return  glm::vec3();
}


glm::vec3
cTransformation3D::ExtrinsicXAxis()  const
{
    return  glm::vec3();
}


glm::vec3
cTransformation3D::ExtrinsicYAxis()  const
{
    return  glm::vec3();
}


glm::vec3
cTransformation3D::ExtrinsicZAxis()  const
{
    return  glm::vec3();
}


glm::vec3
cTransformation3D::VectorForAxis( cEulerAngle::eAxis )  const
{
    return  glm::vec3();
}


/*
//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Parenting API


void  SetParent( cTransformation3D* iParent )
const  cTransformation3D* Parent( cTransformation3D* iParent )  const
void  AddChild( cTransformation3D* iParent )
void  AddChildren( const  std::vector< cTransformation3D* >& iChildren )
const  std::vector< cTransformation3D* >& Children()  const


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Conversion API


glm::vec3  PointToWorld(    const  glm::vec3& iPoint )  const
glm::vec3  PointFromWorld(  const  glm::vec3& iPoint )  const
glm::vec3  PointToParent(   const  glm::vec3& iPoint )  const
glm::vec3  PointFromParent( const  glm::vec3& iPoint )  const
glm::vec3  VecToWorld(      const  glm::vec3& iVec )  const
glm::vec3  VecFromWorld(    const  glm::vec3& iVec )  const
glm::vec3  VecToParent(     const  glm::vec3& iVec )  const
glm::vec3  VecFromParent(   const  glm::vec3& iVec )  const


//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------- Matrix API


glm::mat4 PivotMatrix()  const
glm::mat4 TranslationMatrix()  const
glm::mat4 RotationMatrix()  const
glm::mat4 ScaleMatrix()  const
glm::mat4 Matrix()  const
glm::mat4 InverseMatrix()  const


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------ Private Matrix Update


void
cTransformation3D::InvalidMatrix()  const
{
}


void
cTransformation3D::UpdateMatrix()  const
{
}


void
cTransformation3D::UpdateInverseMatrix()  const
{
}

*/