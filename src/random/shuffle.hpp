#pragma once

#include "rng.hpp"

namespace cpputils {

	template < class T >
	void shuffle(T &val) {
		auto iter = std::begin(val);
		auto n = std::distance(iter, std::end(val));
		auto sequence = rng<>().generate_sequence<std::uniform_int_distribution<decltype(n)>>(n, 0, n - 1);
		auto curr = iter;
		for (auto rn : sequence) {
			std::swap(*(curr++), iter[rn]);
		}
	}

	template < class Iter >
	void shuffle(Iter begin, Iter end) {
		auto n = std::distance(begin, end);
		auto sequence = rng<>().generate_sequence<std::uniform_int_distribution<decltype(n)>>(n, 0, n - 1);
		auto curr = begin;
		for (auto rn : sequence) {
			std::swap(*(curr++), begin[rn]);
		}
	}

	template < class Iter >
	void shuffle(Iter iter, size_t n) {
		auto sequence = rng<>().generate_sequence<std::uniform_int_distribution<decltype(n)>>(n, 0, n - 1);
		auto curr = iter;
		for (auto rn : sequence) {
			std::swap(*(curr++), iter[rn]);
		}
	}

} // namespace cpputils