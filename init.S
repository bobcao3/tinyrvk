.section ".text.init"
.global _start

_start:
la sp, _memory_end
j _cpp_entry
