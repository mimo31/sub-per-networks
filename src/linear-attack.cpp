/**
 * linear-attack.cpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/02/23
 */
#include "linear-attack.hpp"

#include <random>

#include "cor-matrix.hpp"

namespace subpernets
{

std::random_device rnd;

std::mt19937 rg(rnd());

LinearAttack::LinearAttack(const uint32_t boxes, const uint32_t boxsize, const SBox& sbox, const Permutation& p_layer, const uint32_t rounds)
	: boxes(boxes), boxsize(boxsize), sbox(sbox), p_layer(p_layer), rounds(rounds)
{

}

void LinearAttack::generate_path()
{
	auto stboxdist = std::uniform_int_distribution<>(0, boxes - 1);
	const uint32_t start_box = stboxdist(rg);
	uint32_t u0p, w1p;
	const CorrelationMatrix cm(sbox);
	cm.random_entry_mat(rg, u0p, w1p);
	double totalcor = cm.get_cf(u0p, w1p);
	const BitArray u0pb(boxsize, u0p), w1pb(boxsize, w1p);
	BitArray u0 = u0pb, w1 = w1pb;
	for (uint32_t i = 0; i < boxes - 1 - start_box; i++)
	{
		u0 = u0.concat(BitArray(boxsize));
		w1 = w1.concat(BitArray(boxsize));
	}
	for (uint32_t i = 0; i < start_box; i++)
	{
		u0 = BitArray(boxsize).concat(u0);
		w1 = BitArray(boxsize).concat(w1);
	}
	// keep constructing the path
}

void LinearAttack::generate_paths()
{
	
}

}