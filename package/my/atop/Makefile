#
# Copyright (C) 2014-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=atop
PKG_VERSION:=4516bd3

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/Atoptool/atop
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/atop
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=atop
  DEPENDS:=+libncurses +zlib
endef

define Package/atop/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/atop $(1)/usr/bin/
endef

$(eval $(call BuildPackage,atop))


