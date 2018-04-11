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
PKG_HASH:=

include $(INCLUDE_DIR)/host-build.mk

HOST_CONFIGURE_ARGS += \
	--prefix=$(STAGING_DIR_HOST)/ \
	--disable-silent-rules

$(eval $(call HostBuild))
