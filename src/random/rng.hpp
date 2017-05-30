#pragma once
#include <algorithm>
#include <iterator>
#include <random>
#include "iterator/generate.hpp"

namespace cpputils {

	template < class T, size_t S = T::state_size >
	T create_seeded_rng() {
		typename T::result_type seeds[S];
		std::random_device seeder;
		std::generate(std::begin(seeds), std::end(seeds), std::ref(seeder));
		return T(std::seed_seq(std::begin(seeds), std::end(seeds)));
	}

	template < class T = std::mt19937 >
	class rng {
	public:
		using engine_type = T;

	private:
		engine_type m_engine;

	public:
		rng() : m_engine(create_seeded_rng<engine_type>()) {
		}

		rng(const rng&) = delete;
		rng(rng &&r) : m_engine(r.m_engine) {
		}

		rng &operator=(const rng&) = delete;
		rng &operator=(rng &&r) {
			m_engine = std::move(r.m_engine);
			return *this;
		}

		template < class D = std::uniform_int_distribution<>, class... Args >
		typename D::result_type generate(Args... args) {
			return D(typename D::param_type(std::forward<Args>(args)...))(m_engine);
		}

		template < class D = std::uniform_int_distribution<>, class... Args >
		std::vector<typename D::result_type> generate_sequence(size_t n, Args... args) {
			D dist(typename D::param_type(std::forward<Args>(args)...));
			std::vector<typename D::result_type> series;
			series.reserve(n);
			for (size_t i = 0; i < n; ++i) {
				series.push_back(dist(m_engine));
			}
			return series;
		}
	};

} // namespace cpputils