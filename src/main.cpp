#include <iostream>
#include "random/rng.hpp"
#include "time/timer.hpp"

int main() {
	constexpr size_t RNG_TEST_COUNT = 100000000;

	using namespace cpputils;

	volatile double counter = 0.0;
	rng<> gen;
	Timer<> timer;

	std::cout << "Generating " << RNG_TEST_COUNT << " numbers..." << std::endl;
	timer.reset();
	for (size_t i = 0; i < RNG_TEST_COUNT; ++i) {
		counter += gen.generate<>(0, 1);
	}

	std::cout << "Done in " << timer.duration<>() << "ms!" << std::endl;

	std::cout << "Generating " << RNG_TEST_COUNT << " numbers as vector..." << std::endl;
	timer.reset();
	auto res = gen.generate_sequence<>(RNG_TEST_COUNT);
	for (auto e : res) {
		counter += e;
	}

	std::cout << "Done in " << timer.duration<>() << "ms!" << std::endl;
}