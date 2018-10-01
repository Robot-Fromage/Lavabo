/*************************************************************************
*
*   Lavabo
*__________________
*
* main.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include <Windows.h>


#include <QApplication>
#include <QFile>


#include "MainWindow.h"
#include "Program.ProgramRegistry.h"
#include "Program.AllPrograms.h"


int
lavabo_main( int argc, char *argv[] )
{
    QApplication App( argc, argv );

    {
        // Reading and applying style sheet.
        QFile  file( "resources/media/css/style.qss" );
        if( file.open( QFile::ReadOnly ) )
        {
            QString  qss = QLatin1String( file.readAll() );
            App.setStyle( "plastique" );
            App.setStyleSheet( qss );
            file.close();
        }
    }

    auto pr = ::nProgram::ProgramRegistry();
    pr->RegisterProgram( "Template", ::nProgram::nTemplate::RegistryCallback );
    pr->RegisterProgram( "ViewDisplay2D", ::nProgram::nViewDisplay2D::RegistryCallback );
    pr->RegisterProgram( "ViewDisplay3D", ::nProgram::nViewDisplay3D::RegistryCallback );
    pr->RegisterProgram( "ViewDisplay2D_3D", ::nProgram::nViewDisplay2D_3D::RegistryCallback );

    auto w = new cMainWindow();
    w->resize( 870, 600 );
    w->show();

    auto r = App.exec();
    return r;
}


// Debug, application with console.
#ifdef _DEBUG
int
main( int argc, char *argv[] )
{
    return  lavabo_main( argc, argv );
}
#endif


// Release, application without console.
#ifndef _DEBUG
int WINAPI
WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR  lpCmdLine,  int  nCmdShow )
{
    int argc = 0;
    LPWSTR *argList = CommandLineToArgvW( GetCommandLine(), &argc );

    return  lavabo_main( argc, (char**)argList );
}
#endif

