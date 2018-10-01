/*************************************************************************
*
*   Lavabo
*__________________
*
* Program.ProgramRegistry.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "Program.ProgramRegistry.h"


#include <QMap>


namespace  nProgram {


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cProgramRegistry::~cProgramRegistry()
{
    delete  mProgramsMap;
}


cProgramRegistry::cProgramRegistry() :
    mProgramsMap( NULL )
{
    mProgramsMap = new  QMap< QString, ProgramRegistryCallback >();
}

//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- Instance


//static
cProgramRegistry*
cProgramRegistry::Instance()
{
    static cProgramRegistry* sComponentsRegistry = 0;
    if( !sComponentsRegistry )
        sComponentsRegistry = new cProgramRegistry();

    return  sComponentsRegistry;
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------- Registry API


void
cProgramRegistry::RegisterProgram( const  QString& iStr, ProgramRegistryCallback iProgramRegistryCallback )
{
    mProgramsMap->insert( iStr, iProgramRegistryCallback );
}


QWidget*
cProgramRegistry::GetProgram( const  QString& iStr )
{
    if( !mProgramsMap->contains( iStr ) )
        return  NULL;

    ProgramRegistryCallback p = mProgramsMap->value( iStr );
    return p();
}


QList< QString >
cProgramRegistry::Keys()
{
    return  mProgramsMap->keys();
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// Wrapping Singleton Accessor


cProgramRegistry*
ProgramRegistry()
{
    return  cProgramRegistry::Instance();
}


} // namespace nProgram

