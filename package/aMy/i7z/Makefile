#
# Copyright (C) 2014-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=i7z
PKG_VERSION:=1a41ff1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/afontenot/i7z
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

include $(INCLUDE_DIR)/package.mk

define Package/i7z
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=i7z
  DEPENDS:=+libncurses
endef

define Package/i7z/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/i7z $(1)/usr/bin/
endef

$(eval $(call BuildPackage,i7z))


