/*
* =====================================================================================
*
*       Filename:  ReadsChopper.cpp
*
*    Description:  Implenment the ReadsChopper.h
*
*        Version:  1.0
*        Created:  10/09/2015 02:32:11 PM
*       Revision:  none
*       Compiler:  clang++ (ver 3.8)
*
*         Author:  Ke Yang ( keyang@yhgenomics.com )
*   Organization:  YHGenomics
*
* =====================================================================================
*/
#include <stdlib.h>
#include <iostream>
#include "ReadsChopper.h"

using namespace std;
using namespace ReadsPreprocess;

int main( int argc , char *argv [ ] )
{
    cout << "Reads Chopper standy by" << endl;
    ReadsChopper testChopper;
    if( argc > 1 )
    {
        testChopper.FetchPork( argv[1] );
        cout << "Fetch Pork " << argv[1] << endl;
    }
    else
    {
        testChopper.FetchPork( "test.fastq" );
    }

    if( argc > 2 )
    {
        testChopper.SummonButchers( ( size_t )( atoi ( argv [ 2 ] ) ) );
        cout << argv[2] << " Buthcers is on their way" << endl;
    }

    else
    {
        testChopper.SummonButchers( 5 );
    }

    cout << "Dance of the Blades begins" << endl;
    testChopper.ChopFile();

    cout << "Job finished!" << endl;
    testChopper.DeInit();

    return 0;
}
