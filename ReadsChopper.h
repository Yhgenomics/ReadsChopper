/*
 * =====================================================================================
 *
 *       Filename:  ReadsChopper.h
 *
 *    Description:  Chop a big reads file ( .fastq ) into numbers of small files
 *                  with the same format as the big one(that means 4 lines for a read).
 *
 *        Version:  1.0
 *        Created:  10/08/2015 11:01:44 AM
 *       Revision:  none
 *       Compiler:  clang++ (ver 3.8)
 *
 *         Author:  Ke Yang ( keyang@yhgenomics.com )
 *   Organization:  YHGenomics
 *
 * =====================================================================================
 */

#ifndef READS_CHOPPER_H_
#define READS_CHOPPER_H_

//#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// All reads preprocess need to put into this namespace
namespace ReadsPreprocess
{
    using namespace std;

    // Chop the big fastq reads file into small files
    // Guarantee the format in whole  4 lines for a strand(an end)
    // Works for Single end and Pair ends mode both.
    // Need to Check the format error and store it.
    class ReadsChopper
    {
     public:

         // Init
         ReadsChopper();

         // DeInit
         ~ReadsChopper();

         // Reset all the status and allocate the dynamic resources
         size_t Init();

         // Release the the dynamic resources
         size_t DeInit();

         // For the single end mode
         size_t ChopFile();

         // For the pair end mode
         size_t ChopFilePair();

         // Prepare the input file stream
         size_t FetchPork( string reads1 = "", string reads2 = "" );

         // Add one file reader
         size_t AddPork( string readsfile );

         // Set the out put directory
         size_t LocateDiningRoom();

         // Prepare the out file stream
         size_t SummonButchers( size_t num );

     private:

         // Number of the file writes
         size_t butcher_num_;

         // Vector holds the file writers
         vector< ofstream* > butchers_;

         // Filesize thhrolds
         size_t file_size_threshold_;

         // Original big fastq reads file name
         string original_file_name_;

         // Orgianl file reader
         vector< ifstream* > porks_;

         // Out put directory
         string dining_room_;

    };

}//ReadsPreprocess


#endif //READS_CHOPPER_H_
