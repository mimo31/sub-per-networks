/**
 * bitarray.cpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/02/23
 */
#include "bitarray.hpp"

#include <algorithm>

namespace subpernets
{

uint32_t BitArray::segments() const
{
	return (width - 1) / 64 + 1;
}

BitArray::BitArray(const int width)
	: width(width)
{
	const int sgs = segments();
	data = vec<uint64_t>(sgs);
	std::fill(data.begin(), data.end(), 0);
}

BitArray::BitArray(const int width, const vec<uint64_t> data)
	: width(width), data(data)
{
}

BitArray::BitArray(const int width, const uint64_t data)
	: width(width), data(vec<uint64_t>{ data })
{
}

void BitArray::set_bit(const bool val, const int ind)
{
	const int seg = ind / 64;
	const int segind = ind - 64 * seg;
	if (val)
	{
		const uint64_t mask = 1 << segind;
		data[seg] |= mask;
	}
	else
	{
		const uint64_t mask = ~(1 << segind);
		data[seg] &= mask;
	}
}

BitArray BitArray::operator^(const BitArray& other) const
{
	const uint32_t bl = segments();
	vec<uint64_t> newdata(bl);
	for (uint32_t i = 0; i < bl; i++)
		newdata[i] = data[i] ^ other.data[i];
	return BitArray(width, newdata);
}

BitArray& BitArray::operator^=(const BitArray& other)
{
	const uint32_t bl = segments();
	for (uint32_t i = 0; i < bl; i++)
		data[i] ^= other.data[i];
	return *this;
}

bool BitArray::operator[](const int ind) const
{
	const int bl = ind / 64;
	const int rem = ind - 64 * bl;
	return (data[bl] >> rem) & 1;
}

BitArray BitArray::subarray(const int from, const int to) const
{
	const int len = to - from;
	int p0 = from;
	vec<uint64_t> newdata((len - 1) / 64 + 1);
	int nextseg = 0;
	int nexti = 0;
	while (p0 != to)
	{
		const int segafter = p0 / 64 + 1;
		uint64_t trans_bts;
		int trans_len;
		if (segafter * 64 > to)
		{
			trans_bts = data[p0 / 64] & ((1ul << (to % 64)) - 1) >> (p0 % 64);
			trans_len = to - p0;
			p0 = to;
		}
		else
		{
			trans_bts = data[p0 / 64] >> (p0 % 64);
			trans_len = 64 * segafter - p0;
		}
		if (nexti + trans_len > 64)
		{
			newdata[nextseg] |= trans_bts << nexti;
			newdata[nextseg + 1] = trans_bts >> (64 - nexti);
			nextseg++;
			nexti = (nexti + trans_len) % 64;
		}
		else
		{
			newdata[nextseg] |= trans_bts << nexti;
			nexti += trans_len;
			if (nexti == 64)
			{
				nexti = 0;
				nextseg++;
			}
		}
	}
	return BitArray(len, newdata);
}

BitArray BitArray::concat(const BitArray& other) const
{
	const int len = width + other.width;
	vec<uint64_t> newdata((len - 1) / 64 + 1);
	const int sgs0 = other.segments();
	for (int i = 0; i < sgs0; i++)
		newdata[i] = other.data[i];
	int nextseg = width / 64;
	int nexti = width % 64;
	const int sgs1 = segments();
	for (int i = 0; i < sgs1; i++)
	{
		const uint64_t trans_bts = data[i];
		const int trans_len = i == sgs1 - 1 ? (width - 1) % 64 + 1 : 64;
		if (nexti + trans_len > 64)
		{
			newdata[nextseg] |= trans_bts << nexti;
			newdata[nextseg + 1] = trans_bts >> (64 - nexti);
			nextseg++;
			nexti = (nexti + trans_len) % 64;
		}
		else
		{
			newdata[nextseg] |= trans_bts << nexti;
			nexti += trans_len;
			if (nexti == 64)
			{
				nexti = 0;
				nextseg++;
			}
		}
	}
	return BitArray(len, newdata);
}

uint64_t BitArray::get_int() const
{
	return width != 0 ? data[0] : 0;
}

std::ostream& operator<<(std::ostream& os, const BitArray& ba)
{
	for (int i = ba.width - 1; i >= 0; i--)
		os << ba[i];
	return os;
}

}