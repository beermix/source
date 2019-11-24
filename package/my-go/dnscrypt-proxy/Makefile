#
# Copyright (C) 2011-2016 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=dnscrypt-proxy
PKG_VERSION:=bc22f94
PKG_RELEASE:=1
#PKG_GOGET:=github.com/jedisct1/dnscrypt-proxy
PKG_GOGET:=github.com/jedisct1/dnscrypt-proxy/dnscrypt-proxy

GOPKG_SOURCE=GO_$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE).tar.bz2

#!!! uncomment PKG_SOURCE to download fixed version
PKG_SOURCE=$(GOPKG_SOURCE)
PKG_COMMIT=$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/golang.mk

define Package/dnscrypt-proxy
	$(call Package/gopackage/Default)
	TITLE:=dnscrypt-proxy is a simple command line tool that turns your CLI tools into web applications.
	URL:=https://github.com/jedisct1/dnscrypt-proxy
	DEPENDS:=+libgo
endef

define Package/dnscrypt-proxy/description
 dnscrypt-proxy - Share your terminal as a web application.
endef

define Package/dnscrypt-proxy/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/$(PKG_NAME) $(1)/usr/bin
#	$(INSTALL_DIR) $(1)/usr/etc/$(PKG_NAME)
#	$(INSTALL_DATA) $(PKG_BUILD_DIR)/src/$(PKG_GOGET)/.dnscrypt-proxy $(1)/usr/etc/$(PKG_NAME)/dnscrypt-proxy
#	$(SED) 's!~/.!/usr/etc/dnscrypt-proxy/!g' $(1)/usr/etc/$(PKG_NAME)/dnscrypt-proxy
endef

$(eval $(call BuildPackage,dnscrypt-proxy))
