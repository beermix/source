#
# Copyright (C) 2014-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=atop
PKG_VERSION:=2.3.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=https://fossies.org/linux/misc

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/atop
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=atop
  DEPENDS:=+libncurses +zlib
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) CC="$(TARGET_CC)" CFLAGS="$(TARGET_CFLAGS)"
endef

define Package/atop/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/atop $(1)/usr/bin/
endef

$(eval $(call BuildPackage,atop))


