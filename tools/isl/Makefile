#
# Copyright (C) 2009-2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=isl
PKG_VERSION:=0.16.1

PKG_SOURCE_URL:=http://isl.gforge.inria.fr
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_HASH:=45292F30B3CB8B9C03009804024DF72A79E9B5AB89E41C94752D6EA58A1E4B02

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

unexport CFLAGS

HOST_CONFIGURE_ARGS += \
	--enable-static \
	--disable-shared \
	--with-gmp-prefix=$(STAGING_DIR_HOST)

$(eval $(call HostBuild))
