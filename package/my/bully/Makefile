#
# Copyright (C) 2012-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=bully
PKG_VERSION:=17dda79
PKG_REV:=17dda790b9ea7d7026da61429f618ebe58917a8f
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_URL:=https://github.com/Taikson/bully
PKG_SOURCE_PROTO:=git
PKG_SOURCE_VERSION:=$(PKG_REV)
PKG_LICENSE:=GPL-2.0

PKG_USE_MIPS16:=0
PKG_AUTOMAKE_PATHS:=src
PKG_FIXUP:=autoreconf

include $(INCLUDE_DIR)/package.mk

CONFIGURE_PATH:=src
MAKE_PATH:=src

define Package/bully
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=wireless
  TITLE:=Efficient brute force attack against Wifi Protected Setup
  URL:=https://github.com/Taikson/bully
  DEPENDS:=+libpcap +libopenssl
endef

define Package/bully/description
  Reaver targets the external registrar functionality mandated by the WiFi
  Protected Setup specification.
  Access points will provide authenticated registrars with their current
  wireless configuration (including the WPA PSK), and also accept a new
  configuration from the registrar.
endef

define Package/bully/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/bully $(1)/usr/bin/
endef

$(eval $(call BuildPackage,bully))
