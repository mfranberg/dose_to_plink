/**
 * Copyright (c) 2013, Mattias Frånberg
 * All rights reserved.
 *
 * This file is distributed under the Modified BSD License. See the COPYING file
 * for details.
 */

#include <individual.hpp>

Individual::Individual()
    : m_fid( "-" ),
      m_iid( "-" )
{
}

Individual::Individual(std::string fid, std::string iid)
    : m_fid( fid ),
      m_iid( iid ),
      m_doses( )
{
}

Individual::Individual(const Individual &other)
: m_fid( other.m_fid ),
  m_iid( other.m_iid ),
  m_doses( other.m_doses )
{
}

Individual 
Individual::operator=(const Individual &other)
{
    if( this != &other )
    {
        m_fid = other.m_fid;
        m_iid = other.m_iid;
        m_doses.assign( other.m_doses.begin( ), other.m_doses.end( ) );
    }

    return *this;
}

Individual::~Individual()
{
}

std::string 
Individual::get_fid() const
{
    return m_fid;
}

std::string
Individual::get_iid() const
{
    return m_iid;
}

void
Individual::set_fid(const std::string &fid)
{
    m_fid = fid;
}

void
Individual::set_iid(const std::string &iid)
{
    m_iid = iid;
}

void
Individual::add_dose(fixed dose)
{
    m_doses.push_back( dose );
}

fixed 
Individual::get_dose(unsigned int index) const
{
    return m_doses[ index ];
}
