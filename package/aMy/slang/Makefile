#
# Copyright (C) 2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=slang
PKG_VERSION:=2.3.2
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=https://www.jedsoft.org/releases/slang
PKG_HASH:=bbf7f2dcc14e7c7fca40868fd4b411a2bd9e2655

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/slang
  SECTION:=libs
  CATEGORY:=Libraries
  CATEGORY:=Utilities
  DEPENDS:=+libpcre
  TITLE:=slang
endef

# TARGET_CFLAGS += -ffunction-sections -fdata-sections -flto
# TARGET_LDFLAGS += -Wl,--gc-sections

CONFIGURE_ARGS += --without-iconv --without-onig --with-pcre --without-png --without-z --without-x

define Package/slang/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/*.so* $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/*.h $(1)/usr/include/
endef

$(eval $(call BuildPackage,slang))
