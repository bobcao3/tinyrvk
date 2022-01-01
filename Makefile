CXX = clang++
AS = clang
LD = clang
BINARY_DIR = build
MODULE_DIR = $(BINARY_DIR)/modules
TARGET = --target=riscv64 -march=rv64gc -mabi=lp64
CXXFLAGS = -mno-relax -fmodules -g -std=c++20 -fPIC -Ilibcxx/include -O2 -flto=thin
ASMFLAGS = -mno-relax -g -O2
LDFLAGS = -T link.lds -nostdlib

%.S.o: %.S
	$(AS) $(TARGET) $(ASMFLAGS) -c -o $(BINARY_DIR)/$@ $<

%.cpp.o: %.cpp
	$(CXX) $(TARGET) $(CXXFLAGS) -c -o $(BINARY_DIR)/$@ $<

kernel: init.cpp.o uart.cpp.o init.S.o
	$(LD) $(TARGET) $(LDFLAGS) -o $@ $(BINARY_DIR)/*.o