#
# Copyright (C) 2002-2003 Erik Andersen <andersen@uclibc.org>
# Copyright (C) 2004 Manuel Novoa III <mjn3@uclibc.org>
# Copyright (C) 2005-2006 Felix Fietkau <nbd@nbd.name>
# Copyright (C) 2006-2014 OpenWrt.org
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

include $(TOPDIR)/rules.mk

PKG_NAME:=gcc
GCC_VERSION:=$(call qstrip,$(CONFIG_GCC_VERSION))
PKG_VERSION:=$(firstword $(subst +, ,$(GCC_VERSION)))
GCC_DIR:=$(PKG_NAME)-$(PKG_VERSION)

PKG_SOURCE_URL:=@GNU/gcc/gcc-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz

ifeq ($(PKG_VERSION),5.5.0)
  PKG_HASH:=530cea139d82fe542b358961130c69cfde8b3d14556370b65823d2f91f0ced87
endif

ifeq ($(PKG_VERSION),7.5.0)
  PKG_HASH:=b81946e7f01f90528a1f7352ab08cc602b9ccc05d4e44da4bd501c5a189ee661
endif

ifeq ($(PKG_VERSION),7.4.1)
  PKG_VERSION:=7.4.1
  PKG_REV:=7-20190912
  PKG_SOURCE_URL:=ftp://gcc.gnu.org/pub/gcc/snapshots/$(PKG_REV)
  PKG_SOURCE:=gcc-$(PKG_REV).tar.xz
  GCC_DIR:=$(PKG_NAME)-$(GCC_VERSION)
  HOST_BUILD_DIR = $(BUILD_DIR_HOST)/gcc-$(PKG_REV)
endif

ifeq ($(PKG_VERSION),8.3.1)
  PKG_VERSION:=8.3.1
  PKG_REV:=8-20191122
  PKG_SOURCE_URL:=ftp://gcc.gnu.org/pub/gcc/snapshots/$(PKG_REV)
  PKG_SOURCE:=gcc-$(PKG_REV).tar.xz
  GCC_DIR:=$(PKG_NAME)-$(GCC_VERSION)
  HOST_BUILD_DIR = $(BUILD_DIR_HOST)/gcc-$(PKG_REV)
endif

ifeq ($(PKG_VERSION),9.2.0)
  PKG_HASH:=ea6ef08f121239da5695f76c9b33637a118dcf63e24164422231917fa61fb206
endif

ifeq ($(PKG_VERSION),9.2.1)
  PKG_VERSION:=9.2.1
  PKG_REV:=9-20191207
  PKG_SOURCE_URL:=ftp://gcc.gnu.org/pub/gcc/snapshots/$(PKG_REV)
  PKG_SOURCE:=gcc-$(PKG_REV).tar.xz
  GCC_DIR:=$(PKG_NAME)-$(GCC_VERSION)
  HOST_BUILD_DIR = $(BUILD_DIR_HOST)/gcc-$(PKG_REV)
#  PKG_REV:=af9377945330a3062785a9d8b287008d0a531005
#  PKG_SOURCE_URL:=https://github.com/gcc-mirror/gcc/archive
#  PKG_SOURCE:=$(PKG_REV).tar.gz
#  GCC_DIR:=$(PKG_NAME)-$(GCC_VERSION)
#  HOST_BUILD_DIR = $(BUILD_DIR_HOST)/gcc-$(PKG_REV)
endif

ifeq ($(PKG_VERSION),10.0.0)
  PKG_VERSION:=10.0.0
  PKG_REV:=10-20191208
  PKG_SOURCE_URL:=ftp://gcc.gnu.org/pub/gcc/snapshots/$(PKG_REV)
  PKG_SOURCE:=gcc-$(PKG_REV).tar.xz
  GCC_DIR:=$(PKG_NAME)-$(GCC_VERSION)
  HOST_BUILD_DIR = $(BUILD_DIR_HOST)/gcc-$(PKG_REV)
endif

PATCH_DIR=../patches/$(GCC_VERSION)

BUGURL=http://bugs.openwrt.org/
PKGVERSION=OpenWrt GCC $(PKG_VERSION) $(REVISION)

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/toolchain-build.mk

HOST_SOURCE_DIR:=$(HOST_BUILD_DIR)
ifeq ($(GCC_VARIANT),minimal)
  GCC_BUILD_DIR:=$(HOST_BUILD_DIR)-$(GCC_VARIANT)
else
  HOST_BUILD_DIR:=$(HOST_BUILD_DIR)-$(GCC_VARIANT)
  GCC_BUILD_DIR:=$(HOST_BUILD_DIR)
endif

HOST_STAMP_PREPARED:=$(HOST_BUILD_DIR)/.prepared
HOST_STAMP_BUILT:=$(GCC_BUILD_DIR)/.built
HOST_STAMP_CONFIGURED:=$(GCC_BUILD_DIR)/.configured
HOST_STAMP_INSTALLED:=$(HOST_BUILD_PREFIX)/stamp/.gcc_$(GCC_VARIANT)_installed

SEP:=,
TARGET_LANGUAGES:="c,c++$(if $(CONFIG_INSTALL_GFORTRAN),$(SEP)fortran)$(if $(CONFIG_INSTALL_GCCGO),$(SEP)go)"

TAR_OPTIONS += \
	--exclude-from='$(CURDIR)/../exclude-testsuite' --exclude=gcc/ada/*.ad* \
	--exclude=libjava

export libgcc_cv_fixed_point=no
ifdef CONFIG_USE_UCLIBC
  export glibcxx_cv_c99_math_tr1=no
endif
ifdef CONFIG_INSTALL_GCCGO
  export libgo_cv_c_split_stack_supported=no
endif

ifdef CONFIG_GCC_USE_GRAPHITE
  GRAPHITE_CONFIGURE:= --with-isl=$(TOPDIR)/staging_dir/host
else
  GRAPHITE_CONFIGURE:= --without-isl --without-cloog
endif

GCC_CONFIGURE:= \
	SHELL="$(BASH)" \
	$(if $(shell gcc --version 2>&1 | grep LLVM), \
		CFLAGS="-O2 -fbracket-depth=512 -pipe" \
		CXXFLAGS="-O2 -fbracket-depth=512 -pipe" \
	) \
	$(HOST_SOURCE_DIR)/configure \
		--with-bugurl=$(BUGURL) \
		--with-pkgversion="$(PKGVERSION)" \
		--prefix=$(TOOLCHAIN_DIR) \
		--build=$(GNU_HOST_NAME) \
		--host=$(GNU_HOST_NAME) \
		--target=$(REAL_GNU_TARGET_NAME) \
		--with-gnu-ld \
		--enable-target-optspace \
		--enable-checking=release \
		--enable-cld \
		--with-linker-hash-style=gnu \
		--enable-poison-system-directories \
		--with-arch=atom \
		--with-tune=generic \
		--disable-libgomp \
		--disable-libmudflap \
		--disable-multilib \
		--disable-libmpx \
		--disable-nls \
		$(GRAPHITE_CONFIGURE) \
		--with-host-libstdcxx=-lstdc++ \
		$(SOFT_FLOAT_CONFIG_OPTION) \
		$(call qstrip,$(CONFIG_EXTRA_GCC_CONFIG_OPTIONS)) \
		$(if $(CONFIG_mips64)$(CONFIG_mips64el),--with-arch=mips64 \
			--with-abi=$(call qstrip,$(CONFIG_MIPS64_ABI))) \
		$(if $(CONFIG_arc),--with-cpu=$(CONFIG_CPU_TYPE)) \
		--with-gmp=$(TOPDIR)/staging_dir/host \
		--with-mpfr=$(TOPDIR)/staging_dir/host \
		--with-mpc=$(TOPDIR)/staging_dir/host \
		--disable-decimal-float \
		--with-diagnostics-color=auto
ifneq ($(CONFIG_mips)$(CONFIG_mipsel),)
  GCC_CONFIGURE += --with-mips-plt
endif

ifneq ($(CONFIG_GCC_DEFAULT_PIE),)
  GCC_CONFIGURE+= \
		--enable-default-pie
endif

ifneq ($(CONFIG_GCC_DEFAULT_SSP),)
  GCC_CONFIGURE+= \
		--enable-default-ssp
endif

ifneq ($(CONFIG_GCC_LIBSSP),)
  GCC_CONFIGURE+= \
		--enable-libssp
else
  GCC_CONFIGURE+= \
		--disable-libssp
endif

ifneq ($(CONFIG_EXTRA_TARGET_ARCH),)
  GCC_CONFIGURE+= \
		--enable-biarch \
		--enable-targets=$(call qstrip,$(CONFIG_EXTRA_TARGET_ARCH_NAME))-linux-$(TARGET_SUFFIX)
endif

ifdef CONFIG_sparc
  GCC_CONFIGURE+= \
		--enable-targets=all \
		--with-long-double-128
endif

ifeq ($(LIBC),uClibc)
  GCC_CONFIGURE+= \
		--disable-__cxa_atexit
else
  GCC_CONFIGURE+= \
		--enable-__cxa_atexit
endif

ifneq ($(GCC_ARCH),)
  GCC_CONFIGURE+= --with-arch=$(GCC_ARCH)
endif

ifeq ($(CONFIG_arm),y)
  GCC_CONFIGURE+= \
	--with-cpu=$(word 1, $(subst +," ,$(CONFIG_CPU_TYPE)))

  ifneq ($(CONFIG_SOFT_FLOAT),y)
    GCC_CONFIGURE+= \
		--with-fpu=$(word 2, $(subst +, ",$(CONFIG_CPU_TYPE))) \
		--with-float=hard
  endif

  # Do not let TARGET_CFLAGS get poisoned by extra CPU optimization flags
  # that do not belong here. The cpu,fpu type should be specified via
  # --with-cpu and --with-fpu for ARM and not CFLAGS.
  TARGET_CFLAGS:=$(filter-out -m%,$(call qstrip,$(TARGET_CFLAGS)))
endif

ifeq ($(CONFIG_TARGET_x86)$(CONFIG_USE_GLIBC)$(CONFIG_INSTALL_GCCGO),yyy)
  TARGET_CFLAGS+=-fno-split-stack
endif

GCC_MAKE:= \
	export SHELL="$(BASH)"; \
	$(MAKE) \
		CFLAGS="$(HOST_CFLAGS)" \
		CFLAGS_FOR_TARGET="$(TARGET_CFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(TARGET_CFLAGS)" \
		GOCFLAGS_FOR_TARGET="$(TARGET_CFLAGS)"

define Host/SetToolchainInfo
	$(SED) 's,TARGET_CROSS=.*,TARGET_CROSS=$(REAL_GNU_TARGET_NAME)-,' $(TOOLCHAIN_DIR)/info.mk
	$(SED) 's,GCC_VERSION=.*,GCC_VERSION=$(GCC_VERSION),' $(TOOLCHAIN_DIR)/info.mk
endef

ifneq ($(GCC_PREPARE),)
  define Host/Prepare
	$(call Host/SetToolchainInfo)
	$(call Host/Prepare/Default)
	ln -snf $(GCC_DIR) $(BUILD_DIR_TOOLCHAIN)/$(PKG_NAME)
	$(CP) $(SCRIPT_DIR)/config.{guess,sub} $(HOST_SOURCE_DIR)/
	$(SED) 's,^MULTILIB_OSDIRNAMES,# MULTILIB_OSDIRNAMES,' $(HOST_SOURCE_DIR)/gcc/config/*/t-*
	$(SED) 'd' $(HOST_SOURCE_DIR)/gcc/DEV-PHASE
	$(SED) 's, DATESTAMP,,' $(HOST_SOURCE_DIR)/gcc/version.c
	#(cd $(HOST_SOURCE_DIR)/libstdc++-v3; autoconf;);
	$(SED) 's,gcc_no_link=yes,gcc_no_link=no,' $(HOST_SOURCE_DIR)/libstdc++-v3/configure
	mkdir -p $(GCC_BUILD_DIR)
  endef
else
  define Host/Prepare
	mkdir -p $(GCC_BUILD_DIR)
  endef
endif

define Host/Configure
	(cd $(GCC_BUILD_DIR) && rm -f config.cache; \
		$(GCC_CONFIGURE) \
	);
endef

define Host/Clean
	rm -rf $(if $(GCC_PREPARE),$(HOST_SOURCE_DIR)) \
		$(HOST_BUILD_PREFIX)/stamp/.gcc_* \
		$(HOST_BUILD_PREFIX)/stamp/.binutils_* \
		$(GCC_BUILD_DIR) \
		$(BUILD_DIR_TOOLCHAIN)/$(PKG_NAME) \
		$(TOOLCHAIN_DIR)/$(REAL_GNU_TARGET_NAME) \
		$(TOOLCHAIN_DIR)/bin/$(REAL_GNU_TARGET_NAME)-gc* \
		$(TOOLCHAIN_DIR)/bin/$(REAL_GNU_TARGET_NAME)-c*
endef
