/****************************************************************************
 *  mpnumber.cpp                                                            *
 *                                                                          *
 *  João V. M. Andreotti                                                    *
 *                                                                          *
 *  This file contains the implementations of all of the functions defined  *
 *  in the "MPNumber" class present in the file "mpnumber.h"                *
 *                                                                          *
 ****************************************************************************/


#include "mpnumber.h"

#define ABS(x) ((x < 0) ? -x : x)

namespace MPLib
{
    MPNumber MPNumber::multiply(const MPNumber &n)
    {
        throw std::runtime_error("Uninplemented");
    } // TODO(xlonefy): implement

    MPNumber MPNumber::multiply(nint n)
    {
        MPNumber prod;
        prod.reserve(get_size() + 1);
        prod.positive = !(positive ^ ((n < 0) ? false : true)); 

        prod.num.pop_back();

        n = ABS(n);

        unint carry = 0;
        for (auto i = num.begin(); i != num.end(); i++)
        {
            ulint cur_num = n * static_cast<ulint>(*i) + carry;

            prod.num.push_back(static_cast<unint>(cur_num));

            carry = cur_num >> (8 * sizeof(unint));
        }

        prod.num.push_back(carry);
        prod.shrink_to_fit();

        return prod;
    }

    MPNumber MPNumber::pow(uint n)
    {
        MPNumber accumulator(1);
        accumulator.reserve(n * get_size());

        MPNumber squared = *this;
        squared.reserve(2 * n * get_size());

        while (n)
        {
            if (n & 1)
            {
                accumulator = accumulator.multiply(squared);
            }

            squared = squared.square();
            n >>= 1;
        }

        accumulator.shrink_to_fit();
        return accumulator;
    }

    MPNumber MPNumber::square()
    {
        return (*this).multiply(*this);
    }
}