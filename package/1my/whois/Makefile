#
# Copyright (C) 2014-2015 OpenWrt.org
#

include $(TOPDIR)/rules.mk

PKG_NAME:=whois
PKG_VERSION:=4bf6620

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/rfc1036/whois
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

include $(INCLUDE_DIR)/package.mk

define Package/whois
  SECTION:=net
  CATEGORY:=Network
  TITLE:=whois
  URL:=https://github.com/rfc1036/whois
  MENU:=1
endef

define Package/whois/description
  intelligent WHOIS client
endef

define Package/whois/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/whois $(1)/usr/bin/whois
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/whois.conf $(1)/etc/whois.conf
endef

$(eval $(call BuildPackage,whois))
