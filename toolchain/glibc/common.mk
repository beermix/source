#
# Copyright (C) 2006-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
# https://github.com/bminor/glibc/tree/release/2.30/master
# https://github.com/bminor/glibc/tree/release/2.29/master
# https://github.com/bminor/glibc/tree/release/2.28/master
# https://github.com/bminor/glibc/tree/release/2.27/master
# https://sourceware.org/git/gitweb.cgi?p=glibc.git;a=shortlog;h=refs/heads/release/2.30/master
# https://sourceware.org/git/gitweb.cgi?p=glibc.git;a=shortlog;h=HEAD
include $(TOPDIR)/rules.mk

PKG_NAME:=glibc
PKG_VERSION:=2.30
PKG_SOURCE_URL:=@GNU/glibc
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_HASH:=e2c4114e569afbe7edbc29131a43be833850ab9a459d81beb2588016d2bbb8af
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
	unset LD_LIBRARY_PATH; \
	BUILD_CC="$(HOSTCC)" \
	$(TARGET_CONFIGURE_OPTS) \
	CFLAGS="-O2 -g -fno-stack-protector $(filter-out -fomit-frame-pointer -O2 -Os,$(call qstrip,$(TARGET_CFLAGS)))" \
	libc_cv_slibdir="/lib" \
	use_ldconfig=no \
	$(HOST_BUILD_DIR)/$(GLIBC_PATH)configure \
		BASH_SHELL=/bin/bash \
		--prefix= \
		--build=$(GNU_HOST_NAME) \
		--host=$(REAL_GNU_TARGET_NAME) \
		--with-headers=$(TOOLCHAIN_DIR)/include \
		--disable-sanity-checks \
		--enable-bind-now \
		--with-elf \
		--with-tls \
		--with-__thread \
		--disable-profile \
		--disable-werror \
		--without-gd \
		--without-cvs \
		--enable-kernel=4.14 \
		--disable-debug \
		--enable-add-ons \
		--$(if $(CONFIG_SOFT_FLOAT),without,with)-fp

export libc_cv_forced_unwind=yes
export libc_cv_c_cleanup=yes
export libc_cv_ssp=no
export libc_cv_ssp_strong=no
export ac_cv_header_cpuid_h=yes
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
