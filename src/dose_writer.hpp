/**
 * Copyright (c) 2013, Mattias Frånberg
 * All rights reserved.
 *
 * This file is distributed under the Modified BSD License. See the COPYING file
 * for details.
 */

#ifndef __DOSE_WRITER_H__
#define __DOSE_WRITER_H__

#include <iostream>
#include <memory>

#include <individual.hpp>

/**
 * A class that can write minimac .dose files.
 */
class DoseWriter
{
public:
    /**
     * Writes the dose at a specific index in the given individual.
     *
     * @param output The stream to write the dose to.
     * @param individual The individual whose dosage to write.
     * @param index The index of teh dosage to write.
     */
    virtual void write(std::ostream &output, const Individual &individual, unsigned int index);
};

/**
 * A class that can write minimac .prob files.
 */
class ProbWriter
: public DoseWriter
{
public:
    /**
     * Writes the dose of at a specific index in the individual. It is assumed that
     * the dosages are stored so that the individual dose 0 and 1 corresponds to snp1,
     * 2 and 3 to snp2, etc.
     *
     * @param output The stream to write the dose to.
     * @param individual The individual whose dosage to write.
     * @param index The index of the dosage to write.
     */
    virtual void write(std::ostream &output, const Individual &individual, unsigned int index);
};

/**
 * Returns a writer depending on the type. For 'dose'
 * we only need to write one value per snp, but for 'prob'
 * we need to write two.
 *
 * @param type The type of dose to write.
 *
 * @return An appropirate DoseWriter object.
 */
std::auto_ptr<DoseWriter> get_writer(const std::string &type);

#endif /* End of __DOSE_WRITER_H__ */
