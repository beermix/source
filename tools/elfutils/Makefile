#
# Copyright (C) 2009-2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=elfutils
PKG_VERSION:=0.177

PKG_SOURCE_URL:=https://sourceware.org/elfutils/ftp/$(PKG_VERSION)/
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_HASH:=

HOST_BUILD_PARALLEL:=1
HOST_FIXUP:=autoreconf

include $(INCLUDE_DIR)/host-build.mk

unexport CFLAGS

HOST_CONFIGURE_ARGS += \
	utrace_cv_cc_biarch=false \
	--disable-nls \
	--with-zlib \
	--without-bzlib \
	--without-lzma

$(eval $(call HostBuild))
