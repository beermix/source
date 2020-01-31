#
# Copyright (C) 2011-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libcorkipset
PKG_VERSION:=91e42e2
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/rogers0/libcorkipset
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libcorkipset/Default
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=libcorkipset
endef

define Package/libcorkipset/Default/description
endef

define Package/libcorkipset
  $(call Package/libcorkipset/Default)
  TITLE+= libcorkipset
endef

define Package/libcorkipset/description
	$(call Package/libcorkipset/Default/description)
endef

CMAKE_OPTIONS += 

define Build/InstallDev
	$(call Build/InstallDev/cmake,$(1))
endef

define Package/libcorkipset/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libevent-2.1.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libcorkipset))