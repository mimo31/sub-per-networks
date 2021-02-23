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
	uint32_t bits;
	vec<uint32_t> perm;
	vec<uint32_t> rev_perm;
public:
	Permutation(const uint32_t bits, const vec<uint32_t> perm);
	BitArray apply(const BitArray& data) const;
	BitArray rev_apply(const BitArray& data) const;
};

}

#endif // PERMUTATION_HPP