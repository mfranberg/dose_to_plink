#ifndef __LOCUS_H__
#define __LOCUS_H__

#include <string>

/**
 * Represents a locus through its name. Both alleles
 * are stored.
 */
class Locus
{
public:
    /**
     * Constructor.
     *
     * @param name Name of the locus.
     * @param a1 Allele 1 of the locus.
     * @param a2 Allele 2 of the locus.
     */
    Locus(std::string name, std::string a1, std::string a2);

    /**
     * Destructor.
     */
    ~Locus();

    /**
     * Copy constructor.
     *
     * @param other Other locus.
     */
    Locus(const Locus &other);

    /**
     * Assignment operator.
     *
     * @param other Other locus.
     */
    Locus operator=(const Locus &other);

    /**
     * Returns the name of the locus, i.e. rs number.
     *
     * @return The name of the locus.
     */
    std::string get_name() const;

    /**
     * Returns the first allele.
     *
     * @return The first allele.
     */
    std::string get_a1() const;

    /**
     * Returns the second allele.
     *
     * @return The second allele.
     */
    std::string get_a2() const;

private:
    /**
     * Name of the locus.
     */
    std::string m_name;

    /**
     * First allele.
     */
    std::string m_a1;

    /**
     * Second allele.
     */
    std::string m_a2;
};

#endif /* End of __LOCUS_H__ */
