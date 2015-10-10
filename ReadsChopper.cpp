/*
 * =====================================================================================
 *
 *       Filename:  ReadsChopper.cpp
 *
 *    Description:  Implenment the ReadsChopper.h 
 *
 *        Version:  1.0
 *        Created:  10/09/2015 01:20:36 PM
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

// All reads preprocess need to put into this namespace
namespace ReadsPreprocess
{
    size_t my_itoa( size_t val , char* buf )
    {
        const int radix = 10;
        char* p;
        size_t a; //every digit
        size_t len;
        char* b; //start of the digit char
        char temp;

        p = buf;

        b = p;

        do
        {
            a = val % radix;
            val /= radix;
            *p++ = (char)(a + '0');
        }
        while( val > 0 );

        len = ( size_t ) ( p - buf );

        *p-- = 0;

        //swap

        do
        {
            temp = *p;
            *p = *b;
            *b = temp;
            --p;
            ++b;
        }
        while( b < p );

        return len;
    }

    ReadsChopper::ReadsChopper()
    {
        Init();
    }

    ReadsChopper::~ReadsChopper()
    {
        DeInit();
    }

    size_t ReadsChopper::DeInit()
    {
       /*for each ( auto temp_file in porks_ )
       {
           temp_file->close ( );
           delete temp_file;
           temp_file = nullptr;
       }*/
       for( size_t i = 0; i < porks_.size(); i++ )
       {
           porks_ [ i ] -> close();
           delete porks_ [ i ];
           porks_ [ i ] = nullptr;
       }

       porks_.clear();

       /*for each ( auto temp_file in butchers_ )
       {
           temp_file->close ( );
           delete temp_file;
           temp_file = nullptr;
       }*/
       for( size_t i = 0; i < butchers_.size(); i++ )
       {
           butchers_[i] -> close();
           delete butchers_ [ i ];
           butchers_ [ i ] = nullptr;
       }
       butchers_.clear( );

        return 0;
    }

    size_t ReadsChopper::ChopFile()
    {
        if( butcher_num_ == 0 )
        {
            return 1;
        }

        //for each ( auto pork in porks_ )
        for( size_t pi = 0; pi < porks_.size(); pi++ )
        {
            size_t next_butcher = 0;
            size_t readsline = 0;
            string current_reads [ 4 ];
            char tempstr [ 1000 ];
            while( !porks_[pi]->eof() )
            {
                while( !porks_ [ pi ]->eof() && readsline != 4 )
                {
                    porks_ [ pi ]->getline( tempstr , 1000 );
                    string st( tempstr );

                    current_reads [ readsline ] = st;
                    readsline++;
                }

                if( readsline == 4 )
                {
                    /*for each ( auto read in current_reads )
                    {
                        *butchers_ [ next_butcher ] << read << endl;
                    }*/
                    for( size_t i = 0; i < 4;i++)
                    {
                        *butchers_ [ next_butcher ] << current_reads [ i ] << endl;
                    }

                    next_butcher++;
                    if ( next_butcher == butchers_.size( ) )
                    {
                        next_butcher = 0;
                    }
                    readsline = 0;
                }

            }
        }

        return 0;
    }

    size_t ReadsChopper::Init()
    {
        butcher_num_ = 1;
        file_size_threshold_ = 0;
        original_file_name_ = "test.fastq";
        //dining_room_ = "/home/ubuntu/GeneData/diningroom/";
        dining_room_ = "";

        return 0;
    }

    size_t ReadsChopper::AddPork( string readsfile )
    {
        if ( readsfile == "" )
        {
            return 1;
        }
        ifstream* temp_fin = new ifstream ( readsfile.c_str() );
        // TODO ADD the check codes to ensure temp_fin is OK

        porks_.push_back( temp_fin );
        return 0;
    }

    size_t ReadsChopper::SummonButchers( size_t num )
    {
        for( size_t i = 0; i < num; i++ )
        {
            char series_num [ 10 ];
            //_itoa_s ( i , series_num , 10 );
            my_itoa( i , series_num );
            string tempname = original_file_name_ + "sub" + series_num + ".fastq";
            ofstream* temp_file_stream = new ofstream( ( dining_room_ + tempname ) );
            butchers_.push_back( temp_file_stream );
        }

        return 0;
    }

    size_t ReadsChopper::FetchPork( string reads1, string reads2 )
    {
        AddPork( reads1 );
        AddPork( reads2 );

        original_file_name_ = reads1;

        return 0;
    }

}//ReadsPreprocess
