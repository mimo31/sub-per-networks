cmake_minimum_required(VERSION 3.16)

project(sub-per-net)

add_executable(${PROJECT_NAME}
	bitarray.cpp
	cor-matrix.cpp
	linear-attack.cpp
	main.cpp
	permutation.cpp
	program.cpp
	sbox.cpp
	spn.cpp
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
