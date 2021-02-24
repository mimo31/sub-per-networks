/**
 * linear-attack.hpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/02/23
 */
#ifndef LINEAR_ATTACK_HPP
#define LINEAR_ATTACK_HPP

#include "bitarray.hpp"
#include "permutation.hpp"
#include "sbox.hpp"

namespace subpernets
{

class LinearAttack
{
private:
	uint32_t bits;
	uint32_t boxes;
	uint32_t boxsize;
	SBox sbox;
	Permutation p_layer;
	int rounds;
public:
	LinearAttack(const uint32_t boxes, const uint32_t boxsize, const SBox& sbox, const Permutation& p_layer, const uint32_t rounds);
	void generate_path();
	void generate_paths();
};

}

#endif // LINEAR_ATTACK_HPP