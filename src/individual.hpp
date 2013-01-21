#ifndef __INDIVIDUAL_H__
#define __INDIVIDUAL_H__

#include <fixed/fixed.h>

#include <string>
#include <vector>

/**
 * Dosages are only specifed with 4 decimals,
 * so this will save some space compared with a float.
 */
typedef numeric::Fixed<3,13> fixed;

/**
 * Represents an individual through its iid and fid, and
 * stores its dose for each loci.
 */
class Individual
{
public:
    Individual();

    /**
     * Constructor.
     *
     * @param iid Individual identifier.
     * @param fid Familiy indentifier.
     */
    Individual(std::string fid, std::string iid);

    Individual(const Individual &other);

    /**
     * Assignment operator.
     *
     * @param other Other individual.
     */
    Individual operator=(const Individual &other);

    /**
     * Destructor.
     */
    ~Individual();

    /**
     * Returns the fid of the individual, '-' if 
     * it has none.
     *
     * @return the fid of the individual.
     */
    std::string get_fid() const;

    /**
     * Returns the iid of the individual, '-' if 
     * it has none.
     *
     * @return the iid of the individual.
     */
    std::string get_iid() const;


    /**
     * Sets the fid of the individual.
     *
     * @param fid New fid.
     */
    void set_fid(const std::string &fid);

    /**
     * Sets the iid of the individual.
     *
     * @param iid New iid.
     */
    void set_iid(const std::string &iid);

    /**
     * Adds a new dose to the individual.
     *
     * @param dose The dose.
     */
    void add_dose(fixed dose);

    /**
     * Returns the dose for a speicifc locus.
     *
     * @param 
     */
    fixed get_dose(unsigned int index) const;

private:
    /**
     * FID of the individual.
     */
    std::string m_fid;

    /**
     * IID of the individual
     */
    std::string m_iid;

    /**
     * Dose for each marker.
     */
    std::vector<fixed> m_doses;
};

#endif /* End of __INDIVIDUAL_H__ */
