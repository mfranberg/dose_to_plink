#include <algorithm>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <individual.hpp>

#include <fam_util.hpp>

class FixedOrderComparator
{
public:
    FixedOrderComparator(std::map< std::string, unsigned int > id_to_index)
        : m_id_to_index( id_to_index ),
          m_success( true )
    {
    }
    
    FixedOrderComparator(const FixedOrderComparator &other)
        : m_id_to_index( other.m_id_to_index ),
          m_success( true )
    {
    }

    bool was_successful()
    {
        return m_success;
    }

    bool operator()(const Individual &a, const Individual &b)
    {
        std::string a_id = a.get_iid( );
        std::string b_id = b.get_iid( );

        if( m_id_to_index.count( a_id ) < 0 || m_id_to_index.count( b_id ) < 0 )
        {
            m_success = false;
        }

        return m_id_to_index[ a_id ] < m_id_to_index[ b_id ];
    }
private:
    std::map< std::string, unsigned int > m_id_to_index;
    bool m_success;
};


bool
order_individuals(std::vector<Individual> *individuals, const std::string &order_path)
{
    std::ifstream order_file( order_path.c_str( ) );
    std::vector< std::string > order;
    while( !order_file.eof( ) )
    {
        std::string iid;
        order_file >> iid;
        order.push_back( iid );
    }

    return order_individuals( individuals, order );
}

bool
order_individuals(std::vector<Individual> *individuals, const std::vector<std::string> &order)
{
    std::map< std::string, unsigned int > order_map;
    for(unsigned int i = 0; i < order.size( ); i++)
    {
        order_map[ order[ i ] ] = i;
    }

    FixedOrderComparator order_comparator( order_map );
    sort( individuals->begin( ), individuals->end( ), order_comparator );

    return order_comparator.was_successful( );
}

bool
update_individuals(std::vector<Individual> *individuals, const std::string &new_ids_path)
{
    std::ifstream new_ids_file( new_ids_path.c_str( ) );
    fam_map new_ids;
    while( !new_ids_file.eof( ) )
    {
        std::string old_fid;
        std::string old_iid;
        std::string new_fid;
        std::string new_iid;

        new_ids_file >> old_fid >> old_iid >> new_fid >> new_iid;
        new_ids[ old_iid ] = Individual( new_fid, new_iid );
    }

    return update_individuals( individuals, new_ids );
}

bool
update_individuals(std::vector<Individual> *individuals, const fam_map &new_ids)
{
    for(unsigned int i = 0; i < individuals->size( ); i++)
    {
        Individual &person = individuals->at( i );
        fam_map::const_iterator new_person = new_ids.find( person.get_iid( ) );
        if( new_person == new_ids.end( ) )
        {
            printf( "Cannot find: %s\n", person.get_iid( ).c_str( ) );
            return false;
        }

        person.set_iid( new_person->second.get_iid( ) );
        person.set_fid( new_person->second.get_fid( ) );
    }

    return true;
}
