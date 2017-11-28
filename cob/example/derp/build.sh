#!/bin/bash
top_dir=$(cd ../../ && pwd)
build_dir=./build
src_dir=$top_dir/src
bin_name=derp

mkdir -p $build_dir
gcc *.c $src_dir/*.c -o $build_dir/$bin_name
