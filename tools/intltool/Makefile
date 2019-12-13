# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=intltool
PKG_VERSION:=0.51.0

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://launchpad.net/intltool/trunk/$PKG_VERSION/+download/
PKG_HASH:=67c74d94196b153b774ab9f89b2fa6c6ba79352407037c8c14d5aeb334e959cd

include $(INCLUDE_DIR)/host-build.mk

$(eval $(call HostBuild))
