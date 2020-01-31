#
# Copyright (C) 2011-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libbloom
PKG_VERSION:=07136f9

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/jvirkki/libbloom
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

include $(INCLUDE_DIR)/package.mk

define Package/libbloom
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=libbloom
  DEPENDS:=+libpthread +librt
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/bloom.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/build/libbloom.{a,so*} $(1)/usr/lib/
endef

define Package/libbloom/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/build/libbloom.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libbloom))
