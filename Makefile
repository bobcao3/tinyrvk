CLANG ?= clang
OBJCOPY ?= llvm-objcopy
BINARY_DIR = build
MODULE_DIR = $(BINARY_DIR)/modules
TARGET = --target=riscv64 -march=rv64gc -mabi=lp64 -mcmodel=medany
CXXFLAGS = -mno-relax -g -fmodules -std=c++20 -Ilibcxx/include -O2 -flto=thin -fno-threadsafe-statics
ASMFLAGS = -mno-relax -g -O2
LDFLAGS = -T link.lds -nostdlib

CXXSRCS=$(wildcard *.cpp)
CXXOBJS=$(CXXSRCS:.cpp=.cpp.o)

%.S.o: %.S
	$(CLANG) $(TARGET) $(ASMFLAGS) -c -o $(BINARY_DIR)/$@ $<

%.cpp.o: %.cpp
	$(CLANG) $(TARGET) $(CXXFLAGS) -c -o $(BINARY_DIR)/$@ $<

kernel.debug: $(CXXOBJS) init.S.o memset.S.o
	$(CLANG) $(TARGET) $(LDFLAGS) -o $@ $(BINARY_DIR)/*.o

kernel: kernel.debug
	$(OBJCOPY) -S --remove-section .eh_frame --remove-section .riscv.attributes --output-target binary $< $@