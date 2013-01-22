/**
 * Copyright (c) 2013, Mattias Frånberg
 * All rights reserved.
 *
 * This file is distributed under the Modified BSD License. See the COPYING file
 * for details.
 */

#include <locus.hpp>

Locus::Locus(std::string name, std::string a1, std::string a2)
: m_name( name ),
  m_a1( a1 ),
  m_a2( a2 )
{

}

Locus::~Locus()
{
}

Locus::Locus(const Locus &other)
: m_name( other.m_name ),
  m_a1( other.m_a1 ),
  m_a2( other.m_a2 )
{
}

Locus
Locus::operator=(const Locus &other)
{
    if( this != &other )
    {
        m_name = other.m_name;
        m_a1 = other.m_a1;
        m_a2 = other.m_a2;
    }

    return *this;
}

std::string
Locus::get_name() const
{
    return m_name;
}

std::string
Locus::get_a1() const
{
    return m_a1;
}

std::string
Locus::get_a2() const
{
    return m_a2;
}
