#pragma once

#include <cstdint>

class CVarsizedInt {
public:
	static constexpr size_t MaxSize = 9;

	static int CalcSize(uint64_t x);
	static int ParseSize(uint8_t* src);
	static int Encode(uint8_t* dest, uint64_t src);
	static uint64_t Decode(uint8_t* src);
};
