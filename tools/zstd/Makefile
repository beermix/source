#
# Copyright (C) 2006-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=zstd
PKG_VERSION:=1.3.2

PKG_HASH:=ac5054a3c64e6510bc1ae890d05e3d271cc33ceebc9d06ac9f08105766d2798a
PKG_SOURCE_URL:=https://github.com/facebook/zstd/archive
PKG_SOURCE:=v$(PKG_VERSION).tar.gz

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk
include $(INCLUDE_DIR)/package.mk

$(eval $(call HostBuild))
