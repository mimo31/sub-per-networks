/**
 * sbox.cpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/02/23
 */
#include "sbox.hpp"

namespace subpernets
{

SBox::SBox(const int bits, const vec<uint32_t>& table)
	: bits(bits), table(table)
{
	const uint32_t sz = 1 << bits;
	rev_table = vec<uint32_t>(sz);
	for (uint32_t i = 0; i < sz; i++)
		rev_table[table[i]] = i;
}

BitArray SBox::apply_table(const vec<uint32_t>& tb, const int width, const BitArray data) const
{
	const int bl = width / bits;
	BitArray res;
	for (int i = 0; i < bl; i++)
	{
		const BitArray sec = data.subarray((bl - 1 - i) * bits, (bl - i) * bits);
		const BitArray mapped(tb[sec.get_int()]);
		res = res.concat(mapped);
	}
	return res;
}

BitArray SBox::apply(const int width, const BitArray data) const
{
	return apply_table(table, width, data);
}

BitArray SBox::rev_apply(const int width, const BitArray data) const
{
	return apply_table(rev_table, width, data);
}

}