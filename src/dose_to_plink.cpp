/**
 * Copyright (c) 2013, Mattias Frånberg
 * All rights reserved.
 *
 * This file is distributed under the Modified BSD License. See the COPYING file
 * for details.
 */

#include <stdlib.h>
#include <stdio.h>

#include <string>
#include <vector>

#include <optparse/OptionParser.h>

#include <dose_writer.hpp>
#include <fam_util.hpp>
#include <individual.hpp>
#include <locus.hpp>
#include <minimacio.hpp>

using namespace optparse;

/**
 * Parses the options for the program.
 *
 * @param argc Number of arguments, as passed to main.
 * @param argv List of arguments.
 *
 * Note: If arguments cannot be parsed this function exits with an error.
 *
 * @return Parsed arguments.
 */
Values
parse_options(int argc, char *argv[])
{
    const std::string usage = "";
    OptionParser parser = OptionParser( ).usage( "Usage: dose_to_plink [options] -t type -d dose_file -i info_file -o output_file\n"
                                                 "Transposes a minimac .dose or .prob file so that it can be used with plink." );
    char const* const types[] = { "dose", "prob" };
    parser.add_option( "-t" ).metavar( "type" ).help( "Type of dose file 'prob' or 'dose'." );
    parser.add_option( "-d" ).metavar( "dose_file" ).help( "Location of dose file." );
    parser.add_option( "-i" ).metavar( "info_file" ).help( "Location of info file." );
    parser.add_option( "-o" ).metavar( "output_file" ).help( "Outoput file (gzipped)." );

    OptionGroup group = OptionGroup( parser, "Optional parameters" );
    group.add_option( "--alias-file" )
        .help( "Optional: Change names of the FID and IID. The file should contain lines consisting of 'old_fid old_iid new_fid new_iid'." );
    group.add_option( "--order-file" )
        .help( "Optional: The FID and IID will be ordered according to this. The file should contain lines consisting of a single iid." );
    parser.add_option_group( group );

    Values options = parser.parse_args( argc, argv );
    std::vector<std::string> args = parser.args( );
   
    if( args.size( ) > 0 || options.is_set( "t" ) + options.is_set( "d" ) + options.is_set( "i" ) + options.is_set( "o" ) != 4 )
    {
        std::cout << parser.format_help( ) << std::endl;
        exit( 1 );
    }

    return options;
}

int
main(int argc, char *argv[])
{
    Values options = parse_options( argc, argv );

    std::string type = options[ "t" ];
    std::string dose_path = options[ "d" ];
    std::string info_path = options[ "i" ];
    std::string output_path = options[ "o" ];
    
    if( dose_path.find( type ) == std::string::npos )
    {
        printf( "dose_to_plink: warning: Dose filename does not contain the type '%s', continuing anyway.\n", type.c_str( ) );
    }

    std::auto_ptr<DoseWriter> writer = get_writer( type );
    if( writer.get( ) == 0 )
    {
        printf( "dose_to_plink: error: Unkown type %s\n", type.c_str( ) );
        exit( 1 );
    }

    std::vector<Individual> individuals = read_individuals( dose_path );
    std::vector<Locus> loci = read_loci( info_path );

    /* Change names */
    if( options.is_set( "alias_file" ) )
    {
        bool success = update_individuals( &individuals, options[ "alias_file" ] );
        if( !success )
        {
            printf( "dose_to_plink: error: Error in alias file, alias missing." );
            exit( 1 );
        }

    }

    /* Order iids according to file */
    if( options.is_set( "order_file" ) )
    {
        bool success = order_individuals( &individuals, options[ "order_file" ] );
        if( !success )
        {
            printf( "dose_to_plink: error: Error in order file, individual missing." );
            exit( 1 );
        }
    }

    write_plink_file_gz( individuals, loci, output_path, writer );
}
