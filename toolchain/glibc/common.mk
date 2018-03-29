#
# Copyright (C) 2006-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
# https://github.com/bminor/glibc/tree/release/2.27/master
# https://sourceware.org/git/gitweb.cgi?p=glibc.git;a=shortlog;h=refs/heads/release/2.27/master
# -ftree-loop-distribute-patterns -malign-data=abi -fno-semantic-interposition -ftree-vectorize -ftree-loop-vectorize)
include $(TOPDIR)/rules.mk

PKG_NAME:=glibc
PKG_VERSION:=2.27

PKG_SOURCE_PROTO:=git
PKG_SOURCE_VERSION:=39071a55392d2d2e0b75fb19f2b48d661c4cc682
PKG_SOURCE_URL:=git://sourceware.org/git/glibc.git
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.xz

PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
HOST_BUILD_DIR:=$(BUILD_DIR_TOOLCHAIN)/$(PKG_SOURCE_SUBDIR)
CUR_BUILD_DIR:=$(HOST_BUILD_DIR)-$(VARIANT)

PATCH_DIR:=$(PATH_PREFIX)/patches

include $(INCLUDE_DIR)/toolchain-build.mk

HOST_STAMP_PREPARED:=$(HOST_BUILD_DIR)/.prepared
HOST_STAMP_CONFIGURED:=$(CUR_BUILD_DIR)/.configured
HOST_STAMP_BUILT:=$(CUR_BUILD_DIR)/.built
HOST_STAMP_INSTALLED:=$(TOOLCHAIN_DIR)/stamp/.glibc_$(VARIANT)_installed

ifeq ($(ARCH),mips64)
  ifdef CONFIG_MIPS64_ABI_N64
    TARGET_CFLAGS += -mabi=64
  endif
  ifdef CONFIG_MIPS64_ABI_N32
    TARGET_CFLAGS += -mabi=n32
  endif
  ifdef CONFIG_MIPS64_ABI_O32
    TARGET_CFLAGS += -mabi=32
  endif
endif

# -Os miscompiles w. 2.24 gcc5/gcc6
# only -O2 tested by upstream changeset
# "Optimize i386 syscall inlining for GCC 5"
GLIBC_CONFIGURE:= \
	BUILD_CC="$(HOSTCC)" \
	$(TARGET_CONFIGURE_OPTS) \
	CFLAGS="-O2 -m32 -march=bonnell -g $(filter-out "-march=bonnell -march=i686 -O2 -fomit-frame-pointer -m32 -O2 -mfpmath=sse -msse -falign-functions=32 -mno-cx16 -mmmx -msse -msse2 -msse3 -mssse3 -fno-caller-saves -fno-plt --param l1-cache-size=24 --param l1-cache-line-size=64 --param l2-cache-size=512 --param=l1-cache-size=24 --param=l1-cache-line-size=64 --param=l2-cache-size=512 -pipe -fomit-frame-pointer,$(call qstrip,$(TARGET_CFLAGS)))" \
	libc_cv_slibdir="/lib" \
	use_ldconfig=no \
	$(HOST_BUILD_DIR)/$(GLIBC_PATH)configure \
		--prefix= \
		--build=$(GNU_HOST_NAME) \
		--host=$(REAL_GNU_TARGET_NAME) \
		--with-headers=$(TOOLCHAIN_DIR)/include \
		--with-binutils=$(TOOLCHAIN_DIR)/bin \
		BASH_SHELL=/bin/sh \
		--disable-profile \
		--without-selinux \
		--enable-kernel=4.4 \
		--disable-build-nscd \
		--disable-nscd \
		--without-gd \
		--without-cvs \
		--enable-add-ons \
		--disable-timezone-tools \
		--$(if $(CONFIG_SOFT_FLOAT),without,with)-fp

export libc_cv_ssp=no
export libc_cv_ssp_strong=no
export ac_cv_header_cpuid_h=yes
export libc_cv_forced_unwind=yes
export libc_cv_c_cleanup=yes
export HOST_CFLAGS := $(HOST_CFLAGS) -idirafter $(CURDIR)/$(PATH_PREFIX)/include

define Host/SetToolchainInfo
	$(SED) 's,^\(LIBC_TYPE\)=.*,\1=$(PKG_NAME),' $(TOOLCHAIN_DIR)/info.mk
	$(SED) 's,^\(LIBC_URL\)=.*,\1=http://www.gnu.org/software/libc/,' $(TOOLCHAIN_DIR)/info.mk
	$(SED) 's,^\(LIBC_VERSION\)=.*,\1=$(PKG_VERSION),' $(TOOLCHAIN_DIR)/info.mk
	$(SED) 's,^\(LIBC_SO_VERSION\)=.*,\1=$(PKG_VERSION),' $(TOOLCHAIN_DIR)/info.mk
endef

define Host/Configure
	[ -f $(HOST_BUILD_DIR)/.autoconf ] || { \
		cd $(HOST_BUILD_DIR)/; \
		autoconf --force && \
		touch $(HOST_BUILD_DIR)/.autoconf; \
	}
	mkdir -p $(CUR_BUILD_DIR)
	( cd $(CUR_BUILD_DIR); rm -f config.cache; \
		$(GLIBC_CONFIGURE) \
	);
endef

define Host/Prepare
	$(call Host/Prepare/Default)
	ln -snf $(PKG_SOURCE_SUBDIR) $(BUILD_DIR_TOOLCHAIN)/$(PKG_NAME)
endef

define Host/Clean
	rm -rf $(CUR_BUILD_DIR)* \
		$(BUILD_DIR_TOOLCHAIN)/$(LIBC)-dev \
		$(BUILD_DIR_TOOLCHAIN)/$(PKG_NAME)
endef
