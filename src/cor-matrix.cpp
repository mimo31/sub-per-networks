/**
 * cor-matrix.cpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/02/23
 */
#include "cor-matrix.hpp"

#include <cmath>

namespace subpernets
{

bool vecproc(const uint32_t a, const uint32_t b)
{
	uint32_t nd = a & b;
	bool res = false;
	while (nd)
	{
		res ^= nd & 1;
		nd >>= 1;
	}
	return res;
}

CorrelationMatrix::CorrelationMatrix(const SBox& sbox)
	: cf(vec<double>(1 << (2 * sbox.bits))), cfnorm(0), sz(1 << sbox.bits)
{
	const uint32_t sz = 1 << sbox.bits;
	for (uint32_t u = 0; u < sz; u++)
	{
		for (uint32_t v = 0; v < sz; v++)
		{
			uint32_t hits = 0;
			for (uint32_t w = 0; w < sz; w++)
				hits += vecproc(sbox.table[w], u) == vecproc(w, v);
			const double c = 2 * hits / double(sz) - 1;
			cf[u * sz + v] = c;
			cfnorm += std::fabs(c);
		}
	}
}

double CorrelationMatrix::get_cf(const uint32_t u, const uint32_t v) const
{
	return cf[u * sz + v];
}

void CorrelationMatrix::random_entry_mat(rgen rg, uint32_t& u, uint32_t& v) const
{
	std::uniform_real_distribution<> dist(0, cfnorm);
	double val = dist(rg);
	for (uint32_t ui = 0; ui < sz; ui++)
	{
		for (uint32_t vi = 0; vi < sz; vi++)
		{
			val -= cf[ui * sz + vi];
			if (val <= 0)
			{
				u = ui;
				v = vi;
				return;
			}
		}
	}
}

void CorrelationMatrix::random_entry_col(rgen rg, uint32_t& u, const uint32_t v) const
{
	double sm = 0;
	for (uint32_t ui = 0; ui < sz; ui++)
		sm += cf[ui * sz + v];
	std::uniform_real_distribution<> dist(0, sm);
	double val = dist(rg);
	for (uint32_t ui = 0; ui < sz; ui++)
	{
		val -= cf[ui * sz + v];
		if (val <= 0)
		{
			u = ui;
			return;
		}
	}
}

}