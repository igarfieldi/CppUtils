#pragma once

namespace cpputils {
	
	template< class OutputIt, class Size, class Generator, class... Args >
	OutputIt generate_n(OutputIt out, Size n, Generator gen, Args... args) {
		for (Size i = 0; i < n; ++i) {
			*out++ = gen(std::forward<Args>(args)...);
		}
		return out;
	}

} // namespace cpputils