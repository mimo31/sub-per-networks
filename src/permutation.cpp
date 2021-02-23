/**
 * permutation.cpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/02/23
 */
#include "permutation.hpp"

namespace subpernets
{

Permutation::Permutation(const int bits, const vec<int> perm)
	: bits(bits), perm(perm)
{
	rev_perm = vec<int>(bits);
	for (int i = 0; i < bits; i++)
		rev_perm[perm[i]] = i;
}

BitArray Permutation::apply(const BitArray& data)
{
	BitArray res(bits);
	for (int i = 0; i < bits; i++)
		res.set_bit(data[i], perm[i]);
	return res;
}

BitArray Permutation::rev_apply(const BitArray& data)
{
	BitArray res(bits);
	for (int i = 0; i < bits; i++)
		res.set_bit(data[i], rev_perm[i]);
	return res;
}

}