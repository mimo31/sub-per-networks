/**
 * program.cpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/02/23
 */
#include "program.hpp"

#include <cassert>

#include <iomanip>
#include <iostream>

#include "spn.hpp"

namespace subpernets
{

const SBox sbox(4, vec<uint32_t>{
	0x8, 0xf, 0x3, 0x0, 0xa, 0x5, 0x9, 0x6, 0xc, 0x1, 0xe, 0x2, 0x7, 0x4, 0xd, 0xb
});
const Permutation p_layer(16, vec<uint32_t>{
	2, 3, 11, 5, 8, 0, 15, 9, 1, 12, 4, 7, 13, 6, 14, 10
});
constexpr uint32_t boxes = 4;
constexpr uint32_t boxsize = 4;
constexpr uint32_t bits = boxes * boxsize;
constexpr uint32_t rounds = 4;

/**
 * setup data taken from https://www.sent.cz/TK/spn.pdf
 */
void encrypt_decrypt()
{
	const vec<BitArray> keys{
		BitArray(16, 0xb1ac),
		BitArray(16, 0x3170),
		BitArray(16, 0xed23),
		BitArray(16, 0x1aa9),
		BitArray(16, 0x52f1)
	};
	const Spn spn(boxes, boxsize, sbox, p_layer, rounds, keys);
	
	using std::cout;
	cout << std::hex;

	cout << spn.encrypt(BitArray(16, 0x0000)).get_int() << '\n';
	cout << spn.encrypt(BitArray(16, 0xffff)).get_int() << '\n';
	cout << spn.encrypt(BitArray(16, 0x0123)).get_int() << '\n';
	cout << spn.encrypt(BitArray(16, 0xca15)).get_int() << '\n';

	cout << spn.decrypt(BitArray(16, 0x6e25)).get_int() << '\n';
	cout << spn.decrypt(BitArray(16, 0xc1e7)).get_int() << '\n';
	cout << spn.decrypt(BitArray(16, 0xdea4)).get_int() << '\n';
	cout << spn.decrypt(BitArray(16, 0x63ee)).get_int() << '\n';
}

void linear_attack()
{
	
}

void Program::run()
{
	linear_attack();
}

}