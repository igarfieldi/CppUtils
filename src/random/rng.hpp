#pragma once
#include <algorithm>
#include <random>


template < class T, size_t S = T::state_size >
T createSeededRng() {
	typename T::result_type seeds[S];
	std::random_device seeder;
	std::generate(std::begin(seeds), std::end(seeds), std::ref(seeder));
	return T(std::seed_seq(std::begin(seeds), std::end(seeds)));
}

template < class T = std::mt19937 >
class Rng {
private:
	T engine;

public:
	using EngineType = T;

	Rng() : engine(createSeededRng<T>()) {
	}

	template < class D = std::uniform_int_distribution<> >
	typename D::result_type generate(typename const D::param_type &params) {
		return D(params)(engine);
	}

	template < class D = std::uniform_int_distribution<> >
	typename D::result_type generate(typename D::result_type min, typename D::result_type max) {
		return D(min, max)(engine);
	}

	template < class D = std::uniform_int_distribution<> >
	typename D::result_type generate() {
		return D()(engine);
	}
};