#
# Copyright (C) 2009-2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=isl
PKG_VERSION:=0.19

PKG_SOURCE_URL:=http://isl.gforge.inria.fr
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_HASH:=6d6c1aa00e2a6dfc509fa46d9a9dbe93af0c451e196a670577a148feecf6b8a5

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

unexport CFLAGS

HOST_CONFIGURE_ARGS += \
	--enable-static \
	--disable-shared \
	--with-gmp-prefix=$(STAGING_DIR_HOST)

$(eval $(call HostBuild))
