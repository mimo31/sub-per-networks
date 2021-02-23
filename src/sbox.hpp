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
	uint32_t bits;
	vec<uint32_t> table;
	vec<uint32_t> rev_table;

	BitArray apply_table(const vec<uint32_t>& tb, const uint32_t width, const BitArray& data) const;

public:
	SBox(const uint32_t bits, const vec<uint32_t>& table);
	BitArray apply(const uint32_t width, const BitArray& data) const;
	BitArray rev_apply(const uint32_t width, const BitArray& data) const;
};

}

#endif // SBOX_HPP