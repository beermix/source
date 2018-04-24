#
# Copyright (C) 2011-2016 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=gotty
PKG_VERSION:=v1.0.1
PKG_RELEASE:=1
PKG_GOGET:=github.com/yudai/gotty

GOPKG_SOURCE=GO_$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE).tar.xz

#!!! uncomment PKG_SOURCE to download fixed version
#PKG_SOURCE=$(GOPKG_SOURCE)
PKG_COMMIT=$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/golang.mk

define Package/gotty
	$(call Package/gopackage/Default)
	TITLE:=GoTTY is a simple command line tool that turns your CLI tools into web applications.
	URL:=https://github.com/yudai/gotty
	DEPENDS:=+libgo
endef

define Package/gotty/description
 GoTTY - Share your terminal as a web application.
endef

define Package/gotty/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/$(PKG_NAME) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/usr/etc/$(PKG_NAME)
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/src/$(PKG_GOGET)/.gotty $(1)/usr/etc/$(PKG_NAME)/gotty
	$(SED) 's!~/.!/usr/etc/gotty/!g' $(1)/usr/etc/$(PKG_NAME)/gotty
endef

$(eval $(call BuildPackage,gotty))
