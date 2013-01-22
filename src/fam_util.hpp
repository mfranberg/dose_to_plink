/**
 * Copyright (c) 2013, Mattias Frånberg
 * All rights reserved.
 *
 * This file is distributed under the Modified BSD License. See the COPYING file
 * for details.
 */

#ifndef __FAM_UTIL_H__
#define __FAM_UTIL_H__

#include <map>
#include <string>
#include <vector>

#include <individual.hpp>

typedef std::map< std::string, Individual > fam_map;

/**
 * Sorts the individuals according to the order specified
 * in the given file.
 *
 * @param indvidiauls Individuals to order.
 * @param order_path Path to a file that contains an ordering of the individuals.
 *
 * @return true on success, false otherwise.
 */
bool order_individuals(std::vector<Individual> *individuals, const std::string &order_path);

/**
 * Sorts the individuals according to the given order.
 *
 * @param indvidiauls Individuals to order.
 * @param order An ordering of the individuals.
 *
 * @return true on success, false otherwise.
 */
bool order_individuals(std::vector<Individual> *individuals, const std::vector<std::string> &order);

/**
 * Updates the iids and fids of the individuals according to the
 * given file.
 *
 * @param individuals Individuals to update iids and fids.
 * @param new_ids_path Path to a file containing new iids and fids.
 *
 * @return true on success, false otherwise.
 */
bool update_individuals(std::vector<Individual> *individuals, const std::string &new_ids_path);

/**
 * Updates the iids and fids of the individuals according to the
 * given file.
 *
 * @param individuals Individuals to update iids and fids.
 * @param new_ids_path Path to a file containing new iids and fids.
 *
 * @return true on success, false otherwise.
 */
bool update_individuals(std::vector<Individual> *individuals, const fam_map &new_ids);

#endif /* End of __FAM_UTIL_H__ */
