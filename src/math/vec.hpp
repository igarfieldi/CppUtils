#pragma once

#include <array>
#include <assert.h>

namespace cpputils {

	template < size_t N, class T >
	class vector {
	public:
		static constexpr size_t dimensions = N;
		using value_type = T;

	private:
		std::array<T, dimensions> m_data;

	public:
		vector() : m_data() {
		}

		vector(T val) : m_data() {
			m_data.fill(val);
		}

		vector(std::initializer_list<T> list) : m_data() {
			auto iter = m_data.begin();
			for (auto e : list) {
				*(iter++) = e;
				if (iter == m_data.end()) {
					break;
				}
			}
		}

		T &operator[](size_t index) {
			assert(index < dimensions);
			return m_data[index];
		}

		const T &operator[](size_t index) const {
			assert(index < dimensions);
			return m_data[index];
		}
	};

} // namespace cpputils