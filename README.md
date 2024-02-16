# VarsizedInt - Variable-Sized Integer Encoding

VarsizedInt is a C++ package that provides functionality for encoding and decoding variable-sized integers. This encoding scheme is designed to efficiently represent integers of different sizes, optimizing storage space for smaller values while allowing representation of larger integers.

## Installation

To use this package, you can clone the repository and compile it using a C++ compiler:

```bash
git clone https://github.com/NIR3X/VarsizedInt.cpp
cd VarsizedInt.cpp
make
```

## Usage

Here is an example of how to use VarsizedInt in your C++ code:

```cpp
#include "VarsizedInt.h"
#include <iostream>

int main() {
	// Example usage of VarsizedInt encoding and decoding

	// Encode and Decode a variable-sized integer
	uint64_t originalValue = 123456789;
	uint8_t encodedData[CVarsizedInt::MaxSize] = {};
	int encodedSize = CVarsizedInt::Encode(encodedData, originalValue);

	// Display encoded data
	std::cout << "Encoded Data: ";
	for (int i = 0; i < encodedSize; ++i) {
		std::cout << std::hex << (int)encodedData[i] << " ";
	}
	std::cout << std::endl;

	// Decode the data
	uint64_t decodedValue = CVarsizedInt::Decode(encodedData);
	std::cout << "Decoded Value: " << std::dec << decodedValue << " 0x" << std::hex << decodedValue << std::endl;

	return 0;
}
```

In this example, a variable-sized integer (`originalValue`) is encoded using VarsizedInt, and the resulting encoded data is displayed in hexadecimal format. Subsequently, the encoded data is decoded back to its original value. The example showcases the simplicity and effectiveness of VarsizedInt in encoding and decoding variable-sized integers. The `CVarsizedInt::MaxSize` constant represents the maximum size in bytes that an encoded integer can occupy.

## Variable-Sized Integer Ranges and Efficiency

VarsizedInt is designed to efficiently encode variable-sized integers, optimizing storage based on the value range. The following table illustrates the relationship between the value range, encoded size, and the number of bits lost to size encoding:
| Value Range              | Encoded Size | Bits Lost to Size Encoding   |
| ------------------------ | ------------ | ---------------------------- |
| 0 - 127                  | 1 byte       | 1 bit                        |
| 0 - 16383                | 2 bytes      | 2 bits                       |
| 0 - 2097151              | 3 bytes      | 3 bits                       |
| 0 - 268435455            | 4 bytes      | 4 bits                       |
| 0 - 34359738367          | 5 bytes      | 5 bits                       |
| 0 - 4398046511103        | 6 bytes      | 6 bits                       |
| 0 - 562949953421311      | 7 bytes      | 7 bits                       |
| 0 - 72057594037927935    | 8 bytes      | 8 bits                       |
| 0 - 18446744073709551615 | 9 bytes      | 8 bits (limited by encoding) |

Feel free to integrate VarsizedInt into your projects to efficiently store variable-sized integers with reduced storage overhead.

## License

[![GNU AGPLv3 Image](https://www.gnu.org/graphics/agplv3-155x51.png)](https://www.gnu.org/licenses/agpl-3.0.html)

This program is Free Software: You can use, study share and improve it at your
will. Specifically you can redistribute and/or modify it under the terms of the
[GNU Affero General Public License](https://www.gnu.org/licenses/agpl-3.0.html) as
published by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
