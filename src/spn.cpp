/**
 * spn.cpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/02/23
 */
#include "spn.hpp"

namespace subpernets
{

Spn::Spn(const int boxes, const int boxsize, const SBox& sbox, const Permutation& p_layer, const int rounds, const vec<BitArray>& keys)
	: bits(boxes * boxsize), boxes(boxes), boxsize(boxsize), sbox(sbox), p_layer(p_layer), rounds(rounds), keys(keys)
{
}

BitArray Spn::encrypt(const BitArray plaintxt)
{
	BitArray data = plaintxt;
	for (int i = 0; i < rounds - 1; i++)
	{
		data ^= keys[i];
		data = sbox.apply(bits, data);
		data = p_layer.apply(data);
	}
	data ^= keys[rounds - 1];
	data = sbox.apply(bits, data);
	data ^= keys[rounds];
	return data;
}

BitArray Spn::decrypt(const BitArray ciphertxt)
{
	BitArray data = ciphertxt;
	data ^= keys[rounds];
	data = sbox.rev_apply(bits, data);
	data ^= keys[rounds - 1];
	for (int i = rounds - 2; i >= 0; i--)
	{
		data = p_layer.rev_apply(data);
		data = sbox.rev_apply(bits, data);
		data ^= keys[i];
	}
	return data;
}

}