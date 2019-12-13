# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#  PKG_VERSION:=73fc3e7
#

include $(TOPDIR)/rules.mk

PKG_NAME:=gettext-tiny
PKG_VERSION:=55a2119

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/sabotage-linux/gettext-tiny.git
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

include $(INCLUDE_DIR)/host-build.mk

define Host/Compile
	$(MAKE) -C $(HOST_BUILD_DIR) \
		prefix=$(STAGING_DIR_HOST) \
		CFLAGS="$(HOST_CFLAGS)" \
		LDFLAGS="$(HOST_LDFLAGS) -fPIC" \
		LIBINTL=NONE
endef

define Host/Install
	$(MAKE) -C $(HOST_BUILD_DIR) \
		prefix=$(STAGING_DIR_HOST) \
		LIBINTL=NONE \
		install
endef

$(eval $(call HostBuild))
