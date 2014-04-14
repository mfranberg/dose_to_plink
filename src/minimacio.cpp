/**
 * Copyright (c) 2013, Mattias Frånberg
 * All rights reserved.
 *
 * This file is distributed under the Modified BSD License. See the COPYING file
 * for details.
 */

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include <string.h>

#include <gzstream/gzstream.h>

#include <minimacio.hpp>

/**
 * Splits the given line on white space characters into
 * a vector of strings.
 *
 * @param line The line to split.
 *
 * @return A list of strings.
 */
static std::vector<std::string>
split_line(const std::string &line)
{
    char *c_line = strdup( line.c_str( ) );
    std::vector<std::string> splitted_line;
    for( char *word = strtok( c_line, "\t " ); word != NULL; word = strtok( NULL, "\t " ) )
    {
        splitted_line.push_back( word );
    }

    free( c_line );

    return splitted_line;
}

/**
 * Creates an individual from a splitted line that is taken from
 * a .dose file. If the iid and fid cannot be parsed they will be
 * set to '-'.
 *
 * @param splitted_line A line that has been splitted on ' '.
 *
 * @return The individual with all its doses that is represented
 *         by the line.
 */
static Individual
create_individual(const std::vector<std::string> &splitted_line)
{
    std::string header = splitted_line[ 0 ];
    unsigned int sepStart = header.find( "->" );
    
    std::string fid = "-";
    std::string iid = "-";
    if( sepStart != std::string::npos )
    {
        fid = header.substr( 0, sepStart );
        iid = header.substr( sepStart + 2, header.size( ) - sepStart );
    }

    Individual individual( fid, iid );
    for(unsigned int i = 2; i < splitted_line.size( ); i++) // Ignore iid->fid and 'DOSE'
    {
        float dose = strtod( splitted_line[ i ].c_str( ), NULL );
        individual.add_dose( fixed( dose ) );
    }
    
    return individual;
}

/**
 * Creates a locus from a splitted line that is taken from
 * a .info file.
 * 
 * @param splitted_line A line that has been splitted on ' '.
 *
 * @return The individual with all its doses that is represented
 *         by the line.
 */
static Locus
create_locus(const std::vector<std::string> &splitted_line)
{
    return Locus( splitted_line[ 0 ], splitted_line[ 1 ], splitted_line[ 2 ] );
}

void
read_individuals(const std::string &dose_path, std::vector<Individual> *individual_list)
{
    gz::igzstream dose_file( dose_path.c_str( ) );

    // Try to avoid extra copies of the vector when it has
    // to grow.
    individual_list->reserve( 10000 );
   
    std::string line;
    while( std::getline( dose_file, line ) )
    {
        std::vector<std::string> splitted_line = split_line( line );
        Individual individual = create_individual( splitted_line );
        individual_list->push_back( individual );
    }
}

std::vector<Locus>
read_loci(const std::string &info_path)
{
    gz::igzstream info_file( info_path.c_str( ) );

    std::vector<Locus> locus_list;
    std::string line;
    std::getline( info_file, line ); // Skip header
    while( std::getline( info_file, line ) )
    {
        std::vector<std::string> splitted_line = split_line( line );
        Locus locus = create_locus( splitted_line );
        locus_list.push_back( locus );
    }

    return locus_list;
}

void
write_plink_file_gz(const std::vector<Individual> &individuals,
                    const std::vector<Locus> &loci,
                    bool print_header,
                    const std::string &output_path,
                    std::auto_ptr<DoseWriter> writer)
{
    gz::ogzstream output_file( output_path.c_str( ) );
    output_file << std::fixed << std::setprecision( 3 );

    /* Write header. */
    if( print_header )
    {
        output_file << "SNP\tA1\tA2";
        for(unsigned int i = 0; i < individuals.size( ); i++)
        {
            output_file << "\t" << individuals[ i ].get_fid( ) << " " << individuals[ i ].get_iid( );
        }
        output_file << std::endl;
    }

    /* Write doses */
    for(unsigned int i = 0; i < loci.size( ); i++)
    {
        Locus locus = loci[ i ];

        output_file << locus.get_name( ) << "\t" << locus.get_a1( ) << "\t" << locus.get_a2( );
        for(unsigned int j = 0; j < individuals.size( ); j++)
        {
            writer->write( output_file, individuals[ j ], i );
        }
        output_file << std::endl;
    }
}
