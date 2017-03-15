#
# Copyright (C) 2011-2016 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=shadowsocks-local
PKG_VERSION:=2017-01-29
PKG_RELEASE:=1
PKG_GOGET:=github.com/shadowsocks/shadowsocks-local/cmd/shadowsocks-local

GOPKG_SOURCE=GO_$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE).tar.bz2

#!!! uncomment PKG_SOURCE to download fixed version
#PKG_SOURCE=$(GOPKG_SOURCE)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/golang.mk

define Package/shadowsocks-local
	$(call Package/gopackage/Default)
	TITLE:=Execute shell commands via simple http server
	URL:=https://https://github.com/shadowsocks/shadowsocks-local
endef

define Package/shadowsocks-local/description
 Executing shell commands via simple http server (written in Go language).
 Settings through 2 command line arguments, path and shell command. By default bind to :8080.
endef

define Package/shadowsocks-local/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/$(PKG_NAME) $(1)/opt/bin
endef

$(eval $(call BuildPackage,shadowsocks-local))
