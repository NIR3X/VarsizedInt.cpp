AR = ar
CXX = g++
CXXFLAGS = -std=c++2a -Wall -O2 -march=x86-64 -fno-rtti
LDFLAGS = -s -static

SRC = VarsizedInt.cpp
OBJ = $(SRC:.cpp=.o)
DEST = VarsizedInt.a
TEST_SRC = VarsizedIntTest.cpp
TEST_DEST = VarsizedIntTest.exe

build: $(OBJ)
	$(AR) r -o $(DEST) $^

build-test: build
	$(CXX) $(OBJ) $(TEST_SRC) -o $(TEST_DEST) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(DEST) $(TEST_DEST)
