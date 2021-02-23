/**
 * sbox.hpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/02/23
 */
#ifndef SBOX_HPP
#define SBOX_HPP

#include "glob.hpp"

#include "bitarray.hpp"

namespace subpernets
{

class SBox
{
private:
	int bits;
	vec<uint32_t> table;
	vec<uint32_t> rev_table;

	BitArray apply_table(const vec<uint32_t>& tb, const int width, const BitArray data) const;

public:
	SBox(const int bits, const vec<uint32_t>& table);
	BitArray apply(const int width, const BitArray data) const;
	BitArray rev_apply(const int width, const BitArray data) const;
};

}

#endif // SBOX_HPP