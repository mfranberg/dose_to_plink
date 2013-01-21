#include <stdlib.h>
#include <stdio.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

#include <gzstream/gzstream.h>
#include <fixed/fixed.h>

#include <dose_writer.hpp>
#include <fam_util.hpp>
#include <individual.hpp>
#include <locus.hpp>
#include <minimacio.hpp>

namespace po = boost::program_options;

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
po::variables_map
parse_options(int argc, char *argv[])
{
    po::options_description description( "Usage: dose_to_plink [options] --type type --dose-file dose_file --info-file info_file --output_file output_file\nTransposes a minimac .dose or .prob file so that it can be used with plink." );
    description.add_options( )
            ( "help", "Produce a help message." )
            ( "type", po::value< std::string >( ), "Type of dose file: dose or prob." )
            ( "dose-file", po::value< std::string >( ), "Location of dose file." )
            ( "info-file", po::value< std::string >( ), "Location of info file." )
            ( "output-file", po::value< std::string >( ), "Output file (gzipped)." )
            ( "alias-file", po::value< std::string >( ), "Optional: Change names of the FID and IID. Format is lines consisting of old_fid old_iid new_fid new_iid." )
            ( "order-file", po::value< std::string >( ), "Optional: The FID and IID will be ordered according to this. Format is lines consisting of a single iid." );

    po::variables_map args;
    po::store( po::parse_command_line( argc, argv, description ), args );
    po::notify( args );
   
    if( args.count( "help" ) > 0 || args.count( "type" ) + args.count( "dose-file" ) + args.count( "info-file" ) + args.count( "output-file" ) != 4 )
    {
        std::cout << description << std::endl;
        exit( 1 );
    }

    return args;
}

int
main(int argc, char *argv[])
{
    po::variables_map args = parse_options( argc, argv );

    std::string type = args[ "type" ].as< std::string >( );
    std::string dose_path = args[ "dose-file" ].as< std::string >( );
    std::string info_path = args[ "info-file" ].as< std::string >( );
    std::string output_path = args[ "output-file" ].as< std::string >( );
    
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

    if( args.count( "alias-file" ) > 0 )
    {
        bool success = update_individuals( &individuals, args[ "alias-file" ].as< std::string >( ) );
        if( !success )
        {
            printf( "dose_to_plink: error: Error in alias file, alias missing." );
            exit( 1 );
        }

    }
    if( args.count( "order-file" ) > 0 )
    {
        bool success = order_individuals( &individuals, args[ "order-file" ].as< std::string >( ) );
        if( !success )
        {
            printf( "dose_to_plink: error: Error in order file, individual missing." );
            exit( 1 );
        }
    }

    write_plink_file_gz( individuals, loci, output_path, writer );
}
