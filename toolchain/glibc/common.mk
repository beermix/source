#
# Copyright (C) 2006-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
# https://github.com/bminor/glibc/tree/release/2.30/master
# https://github.com/bminor/glibc/tree/release/2.29/master
# https://github.com/bminor/glibc/tree/release/2.28/master
# https://github.com/bminor/glibc/tree/release/2.27/master
# https://sourceware.org/git/gitweb.cgi?p=glibc.git;a=shortlog;h=refs/heads/release/2.31/master
# https://sourceware.org/git/gitweb.cgi?p=glibc.git;a=shortlog;h=refs/heads/release/2.30/master
# https://sourceware.org/git/gitweb.cgi?p=glibc.git;a=shortlog;h=HEAD
include $(TOPDIR)/rules.mk

PKG_NAME:=glibc
PKG_VERSION:=$(call qstrip,$(CONFIG_GLIBC_VERSION))

PKG_SOURCE_URL:=@GNU/glibc
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
GLIBC_PATH:=

ifeq ($(PKG_VERSION),2.23)
  PKG_HASH:=f39f068ce7d749608ff15182b7da28627dd129eaba2687e28bec876d26135629
endif

ifeq ($(PKG_VERSION),2.25)
  PKG_HASH:=94a7a5d7a0094de5b358b340e9b55806f2fe544bc556f3057b6c88a6460fe681
endif

ifeq ($(PKG_VERSION),2.27)
  PKG_HASH:=e49c919c83579984f7c2442243861d04227e8dc831a08d7bf60cdacfdcd08797
endif

ifeq ($(PKG_VERSION),2.31)
  PKG_HASH:=9246fe44f68feeec8c666bb87973d590ce0137cca145df014c72ec95be9ffd17
endif

PATCH_DIR:=$(PATH_PREFIX)/patches/$(PKG_VERSION)

PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
HOST_BUILD_DIR:=$(BUILD_DIR_TOOLCHAIN)/$(PKG_SOURCE_SUBDIR)
CUR_BUILD_DIR:=$(HOST_BUILD_DIR)-$(VARIANT)

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

GLIBC_CONFIGURE:= \
	BUILD_CC="$(HOSTCC)" \
	$(TARGET_CONFIGURE_OPTS) \
	CFLAGS="-O3 -m32 -march=bonnell -mstackrealign $(filter-out -fno-plt -fomit-frame-pointer -fno-caller-saves -fno-plt -march=bonnell -O2 -m32 -Os,$(call qstrip,$(TARGET_CFLAGS)))" \
	libc_cv_slibdir="/lib" \
	use_ldconfig=no \
	$(HOST_BUILD_DIR)/$(GLIBC_PATH)configure \
		BASH_SHELL=/bin/sh \
		--prefix= \
		--build=$(GNU_HOST_NAME) \
		--host=$(REAL_GNU_TARGET_NAME) \
		--with-headers=$(TOOLCHAIN_DIR)/include \
		--disable-profile \
		--disable-werror \
		--without-gd \
		--without-cvs \
		--enable-stack-protector=strong \
		--enable-add-ons \
		--disable-debug \
		$(if $(CONFIG_GLIBC_USE_VERSION_2_31),--enable-obsolete-nsl,) \
		--enable-kernel=5.4.0

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
		cd $(HOST_BUILD_DIR)/$(GLIBC_PATH); \
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
	for f in $(PATCH_DIR).$(ARCH)/*.patch; do \
		patch -p1 -d $(HOST_BUILD_DIR) <  $$$$f; \
	done; \
	ln -snf $(PKG_SOURCE_SUBDIR) $(BUILD_DIR_TOOLCHAIN)/$(PKG_NAME)
endef

define Host/Clean
	rm -rf $(CUR_BUILD_DIR)* \
		$(BUILD_DIR_TOOLCHAIN)/$(LIBC)-dev \
		$(BUILD_DIR_TOOLCHAIN)/$(PKG_NAME)
endef
