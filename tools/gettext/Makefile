#
# Copyright (C) 2010-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=gettext
PKG_VERSION:=0.19.8.1
PKG_HASH:=105556dbc5c3fbbc2aa0edb46d22d055748b6f5c7cd7a8d99f8e7eb84e938be4
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=@GNU/gettext

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

HOST_CFLAGS += $(FPIC)

HOST_CONFIGURE_ARGS += \
	--enable-static --disable-shared \
	--disable-rpath \
	--with-gnu-ld \
	--disable-java \
	--disable-curses \
	--with-included-libxml \
	--disable-native-java \
	--disable-relocatable \
	--disable-libasprintf \
	--disable-csharp \
	--without-emacs \
	--disable-openmp \
	--disable-acl

$(eval $(call HostBuild))
