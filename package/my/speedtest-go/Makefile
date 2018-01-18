#
# Copyright (C) 2011-2016 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=speedtest-go
PKG_VERSION:=git
PKG_RELEASE:=1
PKG_GOGET:=github.com/showwin/speedtest-go

GOPKG_SOURCE=GO_$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE).tar.bz2

#!!! uncomment PKG_SOURCE to download fixed version
#PKG_SOURCE=$(GOPKG_SOURCE)
PKG_COMMIT=90af4664aafc4d9f31647eac4a878625862a12fd

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/golang.mk

define Package/speedtest-go
	$(call Package/gopackage/Default)
	TITLE:=CLI to Test Internet Speed using speedtest.net
	URL:=https://github.com/showwin/speedtest-go
endef

define Package/speedtest-go/description
 GoTTY - Share your terminal as a web application.
endef

define Package/speedtest-go/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/$(PKG_NAME) $(1)/usr/bin
endef

$(eval $(call BuildPackage,speedtest-go))
