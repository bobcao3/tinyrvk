import os

compiler_name = 'clang'
target_options = '--target=riscv64 -march=rv64gc -nostdlib'
cxx_flags = '-g -std=c++20'
lld_flags = '-mno-relax -T link.lds'
binary_dir = 'build'
module_dir = 'build/modules'

def run_cmd(cmd):
    print(cmd)
    os.system(cmd)

def compile_obj(src, out):
    cmd = ' '.join([compiler_name, target_options, cxx_flags, '-c', '-o', os.path.join(binary_dir, out), src])
    run_cmd(cmd)

def compile_module(src):
    module_name = os.path.splitext(src)[0]
    cmd = ' '.join([compiler_name, target_options, cxx_flags, '-emit-module',
        '-o', os.path.join(module_dir, module_name + '.pcm'),
        '-fmodules', 'module.modulemap', '-fmodule-name=' + module_name])
    run_cmd(cmd)

compile_obj('init.S', 'init.S.o')
compile_module('uart.cpp')