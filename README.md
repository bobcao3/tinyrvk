# TinyRVK (Tiny Risc-V Kernel)

Yes, as the title suggested, it's a tiny kernel for Risc-V.

It's probably going to be a micro-kernel.

And it is also an experiment of getting modern C++ to work in kernels.

## Build

Requirements: `LLVM` and `Clang`, with `riscv64` target, `GNU Make` for building the project.

We use `clang` to compile all of our code, and we use `ld.lld` to link the ELF.

Run `make kernel`

## Running on Qemu

We are targeting the Qemu "virt" or "virtio" machine (for now) as real RV64GCV hardware with decent IO options are hard to come by and harder to emulate.

```bash
{path-to-qemu}/qemu-system-riscv64 -machine virt -kernel .\kernel -nographic
```
