#
# Copyright (C) 2012-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=reaver-wps-fork-t6x
PKG_VERSION:=37de8c8

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/t6x/reaver-wps-fork-t6x
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

PKG_AUTOMAKE_PATHS:=src
PKG_FIXUP:=autoreconf

include $(INCLUDE_DIR)/package.mk

CONFIGURE_PATH:=src
MAKE_PATH:=src

define Package/reaver-wps-fork-t6x
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=wireless
  TITLE:=Efficient brute force attack against Wifi Protected Setup
  URL:=https://code.google.com/p/reaver-wps/
  DEPENDS:=+libpcap +libsqlite3
endef

define Package/reaver-wps-fork-t6x/description
  Reaver targets the external registrar functionality mandated by the WiFi
  Protected Setup specification.
  Access points will provide authenticated registrars with their current
  wireless configuration (including the WPA PSK), and also accept a new
  configuration from the registrar.
endef

define Package/reaver-wps-fork-t6x/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/{reaver,wash} $(1)/usr/bin/
endef

$(eval $(call BuildPackage,reaver-wps-fork-t6x))
