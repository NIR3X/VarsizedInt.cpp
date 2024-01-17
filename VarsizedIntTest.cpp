#include "VarsizedInt.h"
#include <cassert>
#include <cstdio>

int main() {
	uint8_t buffer[CVarsizedInt::MaxSize] = {};

	uint64_t testData[] = {
		127, 16383, 2097151, 268435455,
		34359738367ULL, 4398046511103ULL, 562949953421311ULL,
		72057594037927935ULL, 18446744073709551615ULL
	};
	for (int i = 0; i < sizeof(testData) / sizeof(testData[0]); ++i) {
		uint64_t testDataI = testData[i];
		CVarsizedInt::Encode(buffer, testDataI);

		int size = i + 1, sizeRead = CVarsizedInt::ParseSize(buffer);
		uint64_t testDataRead = CVarsizedInt::Decode(buffer);

		printf("%i %i %llu %llu\n", size, sizeRead, testDataI, testDataRead);

		assert(size == sizeRead);
		assert(testDataI == testDataRead);
	}

	puts("PASS");
}
