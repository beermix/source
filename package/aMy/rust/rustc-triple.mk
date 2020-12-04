# To enable rustc/cargo support in your packages, add:
# include $(TOPDIR)/feeds/packages/lang/rustup/rustc-triple.mk
# below include $(TOPDIR)/rules.mk
#
# You will need to add --host=$(RUSTC_TARGET_ARCH) to your packages
# CONFIGURE_VARS to cross-compile for the target architecture

ifeq ($(CONFIG_X86),y)
RUST_ARCH:=i686
else
RUST_ARCH:=i686
endif

CONFIG_HOST_SUFFIX:=$(shell cut -d"-" -f4 <<<"$(GNU_HOST_NAME)")

RUSTC_ARCH_TARGETS:= \
mips64-unknown-linux-gnuabi64 mips64-unknown-linux-muslabi64 \
mips64-unknown-linux-gnuabi64sf mips64-unknown-linux-muslabi64sf \
\
armv7-unknown-linux-gnueabi armv7-unknown-linux-gnueabihf \
armv7-unknown-linux-musleabi \
\
x86_64-unknown-linux-gnu x86_64-unknown-linux-musl

#RUSTC_ARCH_TARGETS:= \
aarch64-unknown-linux-gnu aarch64-unknown-linux-musl \
\
arm-unknown-linux-gnueabi arm-unknown-linux-gnueabihf \
arm-unknown-linux-musleabi arm-unknown-linux-musleabihf \
\
armv4t-unknown-linux-gnueabi \
\
armv5te-unknown-linux-gnueabi armv5te-unknown-linux-musleabi \
\
armv7-unknown-linux-gnueabi armv7-unknown-linux-gnueabihf \
armv7-unknown-linux-musleabi \
\
hexagon-unknown-linux-musl \
\
i386-unknown-linux-gnu i386-unknown-linux-musl \
\
i486-unknown-linux-gnu i486-unknown-linux-musl \
\
i586-unknown-linux-gnu i586-unknown-linux-musl \
\
i686-unknown-linux-gnu i686-unknown-linux-musl \
\
mips-unknown-linux-gnu mips-unknown-linux-musl mips-unknown-linux-uclibc \
\
mips64-unknown-linux-gnuabi64 mips64-unknown-linux-muslabi64 \
mips64-unknown-linux-gnuabi64sf mips64-unknown-linux-muslabi64sf \
\
mips64el-unknown-linux-gnuabi64 mips64el-unknown-linux-muslabi64 \
\
mipsel-unknown-linux-gnu mipsel-unknown-linux-musl \
mipsel-unknown-linux-uclibc \
\
mipsisa32r6-unknown-linux-gnu mipsisa32r6el-unknown-linux-gnu \
\
mipsisa64r6-unknown-linux-gnuabi64 mipsisa64r6el-unknown-linux-gnuabi64 \
\
powerpc-unknown-linux-gnu powerpc-unknown-linux-musl \
\
powerpc64-unknown-linux-gnu powerpc64-unknown-linux-musl \
\
powerpc64le-unknown-linux-gnu powerpc64le-unknown-linux-musl \
\
riscv64gc-unknown-linux-gnu \
\
s390x-unknown-linux-gnu \
\
sparc-unknown-linux-gnu \
\
sparc64-unknown-linux-gnu \
\
thumbv7neon-unknown-linux-gnueabihf thumbv7neon-unknown-linux-musleabihf \
\
x86_64-unknown-linux-gnu x86_64-unknown-linux-musl

RUSTC_HOST_ARCH:= \
	$(strip $(foreach \
		v, \
		$(filter $(HOST_ARCH)-%, $(RUSTC_ARCH_TARGETS)), \
		$(if $(findstring -$(CONFIG_HOST_SUFFIX:"%"=%),$v),$v) \
		) \
	)

RUSTC_TARGET_ARCH_BASE:= \
	$(strip $(foreach \
		v, \
		$(filter $(RUST_ARCH)-%, $(RUSTC_ARCH_TARGETS)), \
		$(if $(findstring -$(CONFIG_TARGET_SUFFIX:"%"=%),$v),$v) \
		) \
	)

#$(info 1 Arch:$(ARCH) RustArch:$(RUST_ARCH) HSuffix:$(CONFIG_HOST_SUFFIX:"%"=%) TSuffix:$(CONFIG_TARGET_SUFFIX:"%"=%) RUSTC_HOST_ARCH:$(RUSTC_HOST_ARCH) RUSTC_TARGET_ARCH_BASE:$(RUSTC_TARGET_ARCH_BASE))

# Check to see if it's a soft-float target
ifeq ($(CONFIG_SOFT_FLOAT),y)
RUSTC_TARGET_ARCH:=$(strip $(filter %sf, $(RUSTC_TARGET_ARCH_BASE)))
else
RUSTC_TARGET_ARCH:=$(strip $(filter-out %sf, $(RUSTC_TARGET_ARCH_BASE)))
endif

# For Testing - Override
#RUSTC_TARGET_ARCH:=i686-unknown-linux-musl

# More than one triple-target remains.
ifneq ($(word 2, $(RUSTC_TARGET_ARCH)),)
$(error RUSTC ERROR: Unsupported or Unknown Target Triple: $(RUSTC_TARGET_ARCH))
endif

# These are environment variables that are used by other packages to
# define where rustc/cargo are kept.
CARGO_HOME:=$(STAGING_DIR_HOSTPKG)
