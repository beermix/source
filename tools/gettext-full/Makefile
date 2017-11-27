#
# Copyright (C) 2009-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=gettext-full
PKG_VERSION:=0.19.8.1

PKG_SOURCE:=gettext-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=@GNU/gettext
PKG_HASH:=105556dbc5c3fbbc2aa0edb46d22d055748b6f5c7cd7a8d99f8e7eb84e938be4
HOST_BUILD_DIR:=$(BUILD_DIR_HOST)/gettext-$(PKG_VERSION)

PKG_MAINTAINER:=Jo-Philipp Wich <jo@mein.io>
PKG_LICENSE:=GPL-3.0+
PKG_CPE_ID:=cpe:/a:gnu:gettext

HOST_BUILD_PARALLEL:=0	
HOST_FIXUP:=autoreconf

include $(INCLUDE_DIR)/host-build.mk

HOST_CONFIGURE_ARGS += \
	--disable-shared \
	--enable-static \
	--enable-silent-rules \
	--disable-libasprintf \
	--disable-rpath \
	--disable-java \
	--disable-native-java \
	--disable-openmp \
	--without-emacs \
	--without-libxml2-prefix

HOST_CONFIGURE_VARS += \
	EMACS="no" \
	am_cv_lib_iconv=no \
	am_cv_func_iconv=no \
	ac_cv_header_iconv_h=no \

$(eval $(call HostBuild))
