/**
 * permutation.hpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/02/23
 */
#ifndef PERMUTATION_HPP
#define PERMUTATION_HPP

#include "glob.hpp"

#include "bitarray.hpp"

namespace subpernets
{

class Permutation
{
private:
	int bits;
	vec<int> perm;
	vec<int> rev_perm;
public:
	Permutation(const int bits, const vec<int> perm);
	BitArray apply(const BitArray& data);
	BitArray rev_apply(const BitArray& data);
};

}

#endif // PERMUTATION_HPP