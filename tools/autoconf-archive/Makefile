# 
# Copyright (C) 2006-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=autoconf-archive
PKG_VERSION:=2018.03.13

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=@GNU/autoconf-archive
PKG_HASH:=6175f90d9fa64c4d939bdbb3e8511ae0ee2134863a2c7bf8d9733819efa6e159

include $(INCLUDE_DIR)/host-build.mk

HOST_FIXUP:=autoreconf

$(eval $(call HostBuild))
