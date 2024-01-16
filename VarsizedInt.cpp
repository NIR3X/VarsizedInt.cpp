#include "VarsizedInt.h"

const size_t CVarsizedInt::MaxSize = 9;

int CVarsizedInt::CalcSize(uint64_t x) {
	size_t size = 0;
	do {
		++size;
	} while (x >>= 7);
	return size > MaxSize ? MaxSize : size;
}

int CVarsizedInt::ParseSize(uint8_t* src) {
	uint8_t x = src[0];
	if ((x & 128) == 0) {
		return 1;
	} else if ((x & (128|64)) == 128) {
		return 2;
	} else if ((x & (128|64|32)) == (128|64)) {
		return 3;
	} else if ((x & (128|64|32|16)) == (128|64|32)) {
		return 4;
	} else if ((x & (128|64|32|16|8)) == (128|64|32|16)) {
		return 5;
	} else if ((x & (128|64|32|16|8|4)) == (128|64|32|16|8)) {
		return 6;
	} else if ((x & (128|64|32|16|8|4|2)) == (128|64|32|16|8|4)) {
		return 7;
	} else if ((x & (128|64|32|16|8|4|2|1)) == (128|64|32|16|8|4|2)) {
		return 8;
	} else if ((x & (128|64|32|16|8|4|2|1)) == (128|64|32|16|8|4|2|1)) {
		return 9;
	}
	return -1;
}

int CVarsizedInt::Encode(uint8_t* dest, uint64_t src) {
	int size = CalcSize(src);
	switch (size) {
		case 1:
			dest[0] = src;
			break;
		case 2:
			dest[0] = 128 | (src >> 8);
			dest[1] = src;
			break;
		case 3:
			dest[0] = 128 | 64 | (src >> 16);
			dest[1] = (src >> 8);
			dest[2] = src;
			break;
		case 4:
			dest[0] = 128 | 64 | 32 | (src >> 24);
			dest[1] = (src >> 16);
			dest[2] = (src >> 8);
			dest[3] = src;
			break;
		case 5:
			dest[0] = 128 | 64 | 32 | 16 | (src >> 32);
			dest[1] = (src >> 24);
			dest[2] = (src >> 16);
			dest[3] = (src >> 8);
			dest[4] = src;
			break;
		case 6:
			dest[0] = 128 | 64 | 32 | 16 | 8 | (src >> 40);
			dest[1] = (src >> 32);
			dest[2] = (src >> 24);
			dest[3] = (src >> 16);
			dest[4] = (src >> 8);
			dest[5] = src;
			break;
		case 7:
			dest[0] = 128 | 64 | 32 | 16 | 8 | 4 | (src >> 48);
			dest[1] = (src >> 40);
			dest[2] = (src >> 32);
			dest[3] = (src >> 24);
			dest[4] = (src >> 16);
			dest[5] = (src >> 8);
			dest[6] = src;
			break;
		case 8:
			dest[0] = 128 | 64 | 32 | 16 | 8 | 4 | 2;
			dest[1] = (src >> 48);
			dest[2] = (src >> 40);
			dest[3] = (src >> 32);
			dest[4] = (src >> 24);
			dest[5] = (src >> 16);
			dest[6] = (src >> 8);
			dest[7] = src;
			break;
		case 9:
			dest[0] = 128 | 64 | 32 | 16 | 8 | 4 | 2 | 1;
			dest[1] = (src >> 56);
			dest[2] = (src >> 48);
			dest[3] = (src >> 40);
			dest[4] = (src >> 32);
			dest[5] = (src >> 24);
			dest[6] = (src >> 16);
			dest[7] = (src >> 8);
			dest[8] = src;
			break;
	}
	return size;
}

uint64_t CVarsizedInt::Decode(uint8_t* src) {
	size_t size = ParseSize(src);
	switch (size) {
		case 1:
			return src[0] & 127;
		case 2:
			return ((src[0] & 63) << 8) | src[1];
		case 3:
			return ((src[0] & 31) << 16) | (src[1] << 8) | src[2];
		case 4:
			return ((src[0] & 15) << 24) |
					(src[1] << 16) |
					(src[2] << 8) |
					 src[3];
		case 5:
			return ((uint64_t)(src[0] & 7) << 32) |
					((uint64_t)src[1] << 24) |
					((uint64_t)src[2] << 16) |
					((uint64_t)src[3] << 8) |
					 (uint64_t)src[4];
		case 6:
			return ((uint64_t)(src[0] & 3) << 40) |
					((uint64_t)src[1] << 32) |
					((uint64_t)src[2] << 24) |
					((uint64_t)src[3] << 16) |
					((uint64_t)src[4] << 8) |
					 (uint64_t)src[5];
		case 7:
			return ((uint64_t)(src[0] & 1) << 48) |
					((uint64_t)src[1] << 40) |
					((uint64_t)src[2] << 32) |
					((uint64_t)src[3] << 24) |
					((uint64_t)src[4] << 16) |
					((uint64_t)src[5] << 8) |
					 (uint64_t)src[6];
		case 8:
			return ((uint64_t)src[1] << 48) |
					((uint64_t)src[2] << 40) |
					((uint64_t)src[3] << 32) |
					((uint64_t)src[4] << 24) |
					((uint64_t)src[5] << 16) |
					((uint64_t)src[6] << 8) |
					 (uint64_t)src[7];
		case 9:
			return ((uint64_t)src[1] << 56) |
					((uint64_t)src[2] << 48) |
					((uint64_t)src[3] << 40) |
					((uint64_t)src[4] << 32) |
					((uint64_t)src[5] << 24) |
					((uint64_t)src[6] << 16) |
					((uint64_t)src[7] << 8) |
					 (uint64_t)src[8];
	}
	return -1;
}
