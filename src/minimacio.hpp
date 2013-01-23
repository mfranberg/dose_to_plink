/**
 * Copyright (c) 2013, Mattias Frånberg
 * All rights reserved.
 *
 * This file is distributed under the Modified BSD License. See the COPYING file
 * for details.
 */

#ifndef __MINIMACIO_H__
#define __MINIMACIO_H__

#include <memory>
#include <string>
#include <vector>

#include <dose_writer.hpp>
#include <individual.hpp>
#include <locus.hpp>

/**
 * Reads all individuals and their doses from a gzipped compressed
 * .dose file.
 *
 * @param dose_path Path the compressed .dose file.
 *
 * @return The list of individuals.
 */
std::vector<Individual> read_individuals(std::string dose_path);

/**
 * Reads all loci and their alleles from a gzipped compressed
 * .info file.
 *
 * @param info_path Path the compressed .info file.
 *
 * @return The list of loci.
 */
std::vector<Locus> read_loci(std::string info_path);

/**
 * Writes a dosage file that can be parsed by plink from
 * a given set of loci and individuals.
 *
 * @param individuals List of individuals and their dosage.
 * @param loci List of loci and their associated info.
 * @param print_header Determines whether to print a header or not.
 * @param output_path Output file.
 * @param writer Determines which typ of dose file to write.
 */
void write_plink_file_gz(const std::vector<Individual> &individuals,
                         const std::vector<Locus> &loci,
                         bool print_header,
                         std::string output_path,
                         std::auto_ptr<DoseWriter> writer);

#endif /* End of __MINIMACIO_H__ */
