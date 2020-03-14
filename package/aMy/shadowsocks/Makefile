#
# Copyright (C) 2014-2020 Jian Chang <aa65535@live.com>
#
# This is free software, licensed under the GNU General Public License v3.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=shadowsocks-libev
PKG_VERSION:=64d3235

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/shadowsocks/shadowsocks-libev.git
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

PKG_LICENSE:=GPLv3
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Jian Chang <aa65535@live.com>

PKG_INSTALL:=0
PKG_USE_MIPS16:=0
PKG_BUILD_PARALLEL:=1
PKG_BUILD_DEPENDS:=c-ares libev libsodium mbedtls pcre libcap

PKG_CONFIG_DEPENDS:= \
	CONFIG_SHADOWSOCKS_WITH_EV \
	CONFIG_SHADOWSOCKS_WITH_PCRE \
	CONFIG_SHADOWSOCKS_WITH_CARES \
	CONFIG_SHADOWSOCKS_WITH_SODIUM \
	CONFIG_SHADOWSOCKS_WITH_MBEDTLS

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/shadowsocks-libev
	SECTION:=net
	CATEGORY:=Network
	TITLE:=Lightweight Secured Socks5 Proxy
	URL:=https://github.com/shadowsocks/shadowsocks-libev
	DEPENDS:=+libpthread \
		+libudns \
		+libcap \
		+!SHADOWSOCKS_WITH_EV:libev \
		+!SHADOWSOCKS_WITH_PCRE:libpcre \
		+!SHADOWSOCKS_WITH_CARES:libcares \
		+!SHADOWSOCKS_WITH_SODIUM:libsodium \
		+!SHADOWSOCKS_WITH_MBEDTLS:libmbedtls
endef

Package/shadowsocks-libev-server = $(Package/shadowsocks-libev)

define Package/shadowsocks-libev/description
Shadowsocks-libev is a lightweight secured socks5 proxy for embedded devices and low end boxes.
endef

Package/shadowsocks-libev-server/description = $(Package/shadowsocks-libev/description)

CMAKE_OPTIONS += -DWITH_DOC_HTML=0 -DWITH_DOC_MAN=0 -DCMAKE_VERBOSE_MAKEFILE=1

define Package/shadowsocks-libev/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/ss-{local,tunnel} $(1)/usr/bin
endef

define Package/shadowsocks-libev-server/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/ss-server $(1)/usr/bin
endef

$(eval $(call BuildPackage,shadowsocks-libev))
$(eval $(call BuildPackage,shadowsocks-libev-server))
