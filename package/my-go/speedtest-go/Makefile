#
# Copyright (C) 2011-2016 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=speedtest-go
PKG_VERSION:=90af466
PKG_RELEASE:=1
PKG_GOGET:=github.com/showwin/speedtest-go 
PKG_GOGET:=gopkg.in/alecthomas/kingpin.v2

GOPKG_SOURCE=GO_speedtest-go-$(PKG_VERSION)-$(PKG_RELEASE).tar.bz2

#!!! uncomment PKG_SOURCE to download fixed version
#PKG_SOURCE=$(GOPKG_SOURCE)
PKG_COMMIT=$(PKG_VERSION)

#do not build both packages in parallel
PKG_BUILD_DEPENDS:=speedtest-go

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/golang.mk

define Package/speedtest-go
	$(call Package/gopackage/Default)
	TITLE:=speedtest-go is a command line program to sync files and directories to and from cloud storages
	URL:=https://github.com/showwin/speedtest-go
	DEPENDS:=+libgo
endef

define Package/speedtest-go/description
 speedtest-go is a command line program to sync files and directories to and from:
endef

define Package/speedtest-go/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/$(PKG_NAME) $(1)/usr/bin
endef

$(eval $(call BuildPackage,speedtest-go))