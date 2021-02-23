/**
 * permutation.cpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/02/23
 */
#include "permutation.hpp"

namespace subpernets
{

Permutation::Permutation(const uint32_t bits, const vec<uint32_t> perm)
	: bits(bits), perm(perm)
{
	rev_perm = vec<uint32_t>(bits);
	for (uint32_t i = 0; i < bits; i++)
		rev_perm[perm[i]] = i;
}

BitArray Permutation::apply(const BitArray& data) const
{
	BitArray res(bits);
	for (uint32_t i = 0; i < bits; i++)
		res.set_bit(data[bits - 1 - i], bits - 1 - perm[i]);
	return res;
}

BitArray Permutation::rev_apply(const BitArray& data) const
{
	BitArray res(bits);
	for (uint32_t i = 0; i < bits; i++)
		res.set_bit(data[bits - 1 - i], bits - 1 - rev_perm[i]);
	return res;
}

}