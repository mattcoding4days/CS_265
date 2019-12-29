#ifndef UTILLITY_HPP
#define UTILLITY_HPP

#include "customExceptions.hpp"
#include "settings.hpp"
#include <string>
#include <vector>

namespace GraderApplication
{
    /* NOTE: Documentation
     * The Utillity class is just that, a collection
     * of methods that perform generic tasks, some are already
     * featured in the C standard or C++ standard library, but
     * have been made more robust for this projects specifications
     * */
    class Utillity
    {
    public:
        /* NOTE: Documentation
         * Strip all comments from the line that is passed
         * */
        void stripComments(std::string &);


        /* NOTE: Documentation
         * search whole or decimal string representation
         * of a number, and return true if there is only
         * digits
         * */
        bool isDigits(std::string &);


        /* NOTE: Documentation
         * convert a string to a float with out the
         * truncating limitations of stof
         * */
        float stringTofloat(const std::string &);


        /* NOTE: Documentation
         * Summ all elements in array
         * */
        float vecSummation(std::vector<float> &);


        /* XXX: Documentation
        * check if string is only alpha numeric
        * */
        bool isAlphaNumeric(std::string &);


        /* XXX: Documentation
        * Convert a string to upper case
        * using transform, code comes from
        * cpp preference transform Documentation
        */
        std::string convert_toupper(std::string &);
    };
};

#endif
