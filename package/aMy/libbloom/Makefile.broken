#
# Copyright (C) 2011-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libbloom
PKG_VERSION:=1.6
PKG_RELEASE:=1

PKG_SOURCE:=v$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/jvirkki/libbloom/archive

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/libbloom/Default
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=libbloom
  DEPENDS:=+check
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
