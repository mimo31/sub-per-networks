/**
 * spn.hpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/02/23
 */
#ifndef SPN_HPP
#define SPN_HPP

#include <vector>

#include "glob.hpp"

#include "bitarray.hpp"
#include "permutation.hpp"
#include "sbox.hpp"

namespace subpernets
{

class Spn
{
private:
	int bits;
	int boxes;
	int boxsize;
	SBox sbox;
	Permutation p_layer;
	int rounds;
	vec<BitArray> keys;

public:
	Spn(const int boxes, const int boxsize, const SBox& sbox, const Permutation& p_layer, const int rounds, const vec<BitArray>& keys);
	BitArray encrypt(const BitArray& plaintxt) const;
	BitArray decrypt(const BitArray& ciphertxt) const;
};

}

#endif // SPN_HPP