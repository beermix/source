#!/bin/bash
 2 export CARGO_TARGET_MIPS_UNKNOWN_LINUX_MUSL_LINKER=/home/user/ledex/staging_dir/toolchain-i386_pentium4_gcc-9.3.0_musl/bin/i486-openwrt-linux-musl-gcc
 3 export TARGET_CC=/home/user/ledex/staging_dir/toolchain-i386_pentium4_gcc-9.3.0_musl/bin/i486-openwrt-linux-musl-gcc
 4 export HOST_CC=gcc
 5 export MIPS_UNKNOWN_LINUX_MUSL_OPENSSL_DIR=/home/user/ledex/staging_dir/target-i386_pentium4_musl/usr/
 6 export PKG_CONFIG_ALLOW_CROSS=1
 7 cargo build --target i686-unknown-linux-musl --release
