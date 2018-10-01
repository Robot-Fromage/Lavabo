/*************************************************************************
*
*   Lavabo
*__________________
*
* Program.ProgramRegistry.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


#include <QWidget>


namespace  nProgram {


typedef QWidget* (*ProgramRegistryCallback)();


class cProgramRegistry
{
    typedef cProgramRegistry    tSelf;

private:
    // Construction / Destruction
    virtual  ~cProgramRegistry();
    cProgramRegistry();

public:
    // Instance
    static  cProgramRegistry* Instance();

public:
    // Registry API
    void  RegisterProgram( const  QString& iStr, ProgramRegistryCallback iProgramRegistryCallback );
    QWidget*  GetProgram( const  QString& iStr );
    QList< QString > Keys();

private:
    // Data
    QMap< QString, ProgramRegistryCallback >* mProgramsMap;
};


// Wrapping Singleton Accessor
cProgramRegistry* ProgramRegistry();


} // namespace nProgram

