#
# Copyright (C) 2009-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=gettext
PKG_VERSION:=0.19.8.1

PKG_SOURCE_URL:=@GNU/gettext/
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_HASH:=ff942af0e438ced4a8b0ea4b0b6e0d6d657157c5e2364de57baa279c1c125c43

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

HOST_CONFIGURE_ARGS += \
	--enable-static \
	--disable-shared \
	--disable-rpath \
	--with-gnu-ld \
	--disable-java \
	--disable-curses \
	--with-included-libxml \
	--disable-native-java \
	--disable-csharp \
	--without-emacs \
	--disable-openmp

HOST_CFLAGS += $(HOST_FPIC)

$(eval $(call HostBuild))
