#include <iostream>
#include <string>
#include "math/vec.hpp"
#include "random/rng.hpp"
#include "random/shuffle.hpp"
#include "time/timer.hpp"

void print() {
}

template < class T, class... Args >
void print(T val, Args ...args) {
	std::cout << val << " ";
	print(std::forward<Args>(args)...);
}

template < class E, class D, class... Args >
void testRng(size_t count, const std::string &engineName, const std::string &distName, Args... args) {
	using namespace cpputils;

	volatile typename D::result_type counter = typename D::result_type();
	rng<E> gen;
	Timer<> timer;

	std::cout << "RNG test for '" << engineName << "' and '" << distName << "' with [ ";
	print(std::forward<Args>(args)...);
	/*for (auto p : params) {
		std::cout << p << " ";
	}*/
	std::cout << "] as parameters and " << count << " numbers" << std::endl;
	timer.reset();
	for (size_t i = 0; i < count; ++i) {
		counter += gen.generate<D>(std::forward<Args>(args)...);
	}

	std::cout << "Loop:     " << timer.duration<>() << "ms" << std::endl;

	timer.reset();
	auto res = gen.generate_sequence<D>(count, std::forward<Args>(args)...);
	for (auto e : res) {
		counter += e;
	}

	std::cout << "Sequence: " << timer.duration<>() << "ms" << std::endl << std::endl;
}

void testRng() {
	constexpr size_t TEST_NUM = 10000000u;

	testRng<std::mt19937, std::uniform_int_distribution<int>>(TEST_NUM, "mt19937", "uniform_int_distribution(32)");
	testRng<std::mt19937, std::uniform_int_distribution<long long>>(TEST_NUM, "mt19937", "uniform_int_distribution(64)");
	testRng<std::mt19937, std::uniform_real_distribution<float>>(TEST_NUM, "mt19937", "uniform_real_distribution(32)");
	testRng<std::mt19937, std::uniform_real_distribution<double>>(TEST_NUM, "mt19937", "uniform_real_distribution(64)");

	testRng<std::mt19937, std::uniform_int_distribution<int>>(TEST_NUM, "mt19937", "uniform_int_distribution(32)", 0, 1);
	testRng<std::mt19937, std::uniform_int_distribution<long long>>(TEST_NUM, "mt19937", "uniform_int_distribution(64)", 0, 1);
	testRng<std::mt19937, std::uniform_real_distribution<float>>(TEST_NUM, "mt19937", "uniform_real_distribution(32)", 0.0f, 1.0f);
	testRng<std::mt19937, std::uniform_real_distribution<double>>(TEST_NUM, "mt19937", "uniform_real_distribution(64)", 0.0, 1.0);

	testRng<std::mt19937_64, std::uniform_int_distribution<int>>(TEST_NUM, "mt19937_64", "uniform_int_distribution(32)");
	testRng<std::mt19937_64, std::uniform_int_distribution<long long>>(TEST_NUM, "mt19937_64", "uniform_int_distribution(64)");
	testRng<std::mt19937_64, std::uniform_real_distribution<float>>(TEST_NUM, "mt19937_64", "uniform_real_distribution(32)");
	testRng<std::mt19937_64, std::uniform_real_distribution<double>>(TEST_NUM, "mt19937_64", "uniform_real_distribution(64)");

	testRng<std::mt19937_64, std::uniform_int_distribution<int>>(TEST_NUM, "mt19937_64", "uniform_int_distribution(32)", 0, 1);
	testRng<std::mt19937_64, std::uniform_int_distribution<long long>>(TEST_NUM, "mt19937_64", "uniform_int_distribution(64)", 0, 1);
	testRng<std::mt19937_64, std::uniform_real_distribution<float>>(TEST_NUM, "mt19937_64", "uniform_real_distribution(32)", 0.0f, 1.0f);
	testRng<std::mt19937_64, std::uniform_real_distribution<double>>(TEST_NUM, "mt19937_64", "uniform_real_distribution(64)", 0.0, 1.0);
}

void testVec() {
	using namespace cpputils;

	vector<3, double> v{ 1, 2 };
	std::cout << v[2] << std::endl;
}

void testShuffle() {
	using namespace cpputils;

	std::vector<size_t> v{ 1, 2, 3, 4, 5, 6 };
	shuffle(v);
	for (const auto &e : v) {
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

int main() {
	//testRng();
	//testVec();
	testShuffle();

	std::cin.get();
}