#
# Copyright (C) 2014-2015 OpenWrt.org
#

include $(TOPDIR)/rules.mk

PKG_NAME:=whois
PKG_VERSION:=5.3.0

PKG_SOURCE_URL:=http://ftp.debian.org/debian/pool/main/w/whois
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_NAME)_$(PKG_VERSION).tar.xz

include $(INCLUDE_DIR)/package.mk

define Package/whois
  SECTION:=net
  CATEGORY:=Network
  DEPENDS:=+gettext-full/host +libidn2
  TITLE:=whois
  URL:=https://github.com/rfc1036/whois
  MENU:=1
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) CONFIG_FILE="/etc/whois.conf" HAVE_ICONV=1
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
