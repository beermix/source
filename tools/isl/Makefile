#
# Copyright (C) 2009-2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=isl
PKG_VERSION:=0.21

PKG_SOURCE_URL:=http://isl.gforge.inria.fr
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
#PKG_HASH:=45292f30b3cb8b9c03009804024df72a79e9b5ab89e41c94752d6ea58a1e4b02

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

unexport CFLAGS

HOST_CONFIGURE_ARGS += \
	--enable-static \
	--disable-shared \
	--with-gmp-prefix=$(STAGING_DIR_HOST)

$(eval $(call HostBuild))
