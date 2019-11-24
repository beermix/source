#
# Copyright (C) 2011-2016 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=speedtest-go
PKG_VERSION:=v1.0.3
PKG_RELEASE:=1
PKG_GOGET:=github.com/showwin/speedtest-go

GOPKG_SOURCE=GO_$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE).tar.bz2

#!!! uncomment PKG_SOURCE to download fixed version
PKG_SOURCE=$(GOPKG_SOURCE)
PKG_COMMIT=$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/golang.mk

define Package/speedtest-go
	$(call Package/gopackage/Default)
	TITLE:=speedtest-go is a simple command line tool that turns your CLI tools into web applications.
	URL:=https://github.com/showwin/speedtest-go
	DEPENDS:=+libgo
endef

define Package/speedtest-go/description
 speedtest-go - Share your terminal as a web application.
endef

define Package/speedtest-go/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/$(PKG_NAME) $(1)/usr/bin
endef

$(eval $(call BuildPackage,speedtest-go))
