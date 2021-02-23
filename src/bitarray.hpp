/**
 * bitarray.hpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/02/23
 */
#ifndef BITARRAY_HPP
#define BITARRAY_HPP

#include <cstdint>
#include <iostream>

#include "glob.hpp"

namespace subpernets
{

class BitArray
{
private:
	int width = 0;
	vec<uint64_t> data;

	uint32_t segments() const;

public:
	BitArray() = default;
	BitArray(const int width); // zero-initialize
	BitArray(const int width, const vec<uint64_t> data);
	BitArray(const int width, const uint64_t data);

	void set_bit(const bool val, const int ind);

	BitArray operator^(const BitArray& other) const;
	BitArray& operator^=(const BitArray& other);
	bool operator[](const int ind) const;

	BitArray subarray(const int from, const int to) const;
	BitArray concat(const BitArray& other) const;

	uint64_t get_int() const;

	friend std::ostream& operator<<(std::ostream&, const BitArray&);
};

std::ostream& operator<<(std::ostream& os, const BitArray& ba);

}

#endif // BITARRAY_HPP