/**
 * cor-matrix.hpp
 * 
 * Author: Viktor Fukala
 * Created on 2021/02/23
 */
#ifndef COR_MATRIX_HPP
#define COR_MATRIX_HPP

#include "glob.hpp"

#include "sbox.hpp"

namespace subpernets
{

class CorrelationMatrix
{
private:
	vec<double> cf;
	double cfnorm;
	uint32_t sz;
public:
	CorrelationMatrix(const SBox& sbox);
	double get_cf(const uint32_t u, const uint32_t v) const;
	void random_entry_mat(rgen rg, uint32_t& u, uint32_t& v) const;
	void random_entry_col(rgen rg, uint32_t& u, const uint32_t v) const;
};

}

#endif // COR_MATRIX_HPP