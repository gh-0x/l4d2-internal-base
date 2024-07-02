#pragma once

#include <string>
#include <array>
#include <cstdarg>
#include <cstdint>
#include <immintrin.h>

namespace X
{
	constexpr auto time = __TIME__;
	constexpr auto seed = static_cast<int>(time[7]) + static_cast<int>(time[6]) * 10 + static_cast<int>(time[4]) * 60 + static_cast<int>(time[3]) * 600 + static_cast<int>(time[1]) * 3600 + static_cast<int>(time[0]) * 36000;

	template < int N >
	struct rndm_gen {
	private:
		static constexpr unsigned a = 16807; // 7^5
		static constexpr unsigned m = 2147483647; // 2^31 - 1

		static constexpr unsigned s = rndm_gen< N - 1 >::value;
		static constexpr unsigned lo = a * (s & 0xFFFF); // Multiply lower 16 bits by 16807
		static constexpr unsigned hi = a * (s >> 16); // Multiply higher 16 bits by 16807
		static constexpr unsigned lo2 = lo + ((hi & 0x7FFF) << 16); // Combine lower 15 bits of hi with lo's upper bits
		static constexpr unsigned hi2 = hi >> 15; // Discard lower 15 bits of hi
		static constexpr unsigned lo3 = lo2 + hi;

	public:
		static constexpr unsigned max = m;
		static constexpr unsigned value = lo3 > m ? lo3 - m : lo3;
	};

	template < >
	struct rndm_gen< 0 > {
		static constexpr unsigned value = seed;
	};

	template < int N, int M >
	struct random_int {
		static constexpr auto value = rndm_gen< N + 1 >::value % M;
	};

	template < int N >
	struct random_char {
		static const char value = static_cast<char>(1 + random_int< N, 0x7F - 1 >::value);
	};

	template < size_t N, int K >
	struct xor_str_init_t {
	private:
		const char _key;
		std::array< char, N + 1 > _encrypted;

		constexpr char enc(char c) const {
			return c ^ _key;
		}

		char dec(char c) const {
			return c ^ _key;
		}

	public:
		template < size_t... Is >
		constexpr __forceinline xor_str_init_t(const char* str, std::index_sequence< Is... >) : _key(random_char< K >::value), _encrypted{ enc(str[Is])... } {
		}

		__forceinline decltype(auto) decrypt(void) {
			for (size_t i = 0; i < N; ++i) {
				_encrypted[i] = dec(_encrypted[i]);
			}
			_encrypted[N] = '\0';
			return _encrypted.data();
		}
	};
};

#define xorstr_( s ) ( X::xor_str_init_t< sizeof( s ) - 1, __COUNTER__ >( s, std::make_index_sequence< sizeof( s ) - 1>() ).decrypt() )

#ifdef _DEBUG
#define X_( s ) ( s )
#else
#define X_( s ) xorstr_( s )
#endif
