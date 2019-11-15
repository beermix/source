# 
# Copyright (C) 2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=bc
PKG_VERSION:=1.07.1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=ftp://ftp.gnu.org/gnu/bc/
PKG_HASH:=

HOST_FIXUP:=autoreconf

include $(INCLUDE_DIR)/host-build.mk

$(eval $(call HostBuild))
