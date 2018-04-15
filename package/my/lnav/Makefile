#
# Copyright (C) 2014-2017 Jian Chang <aa65535@live.com>
#
# This is free software, licensed under the GNU General Public License v3.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=lnav
PKG_VERSION:=873fc4d

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/tstack/lnav
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=4b40b3f9f59c8825af0cb927c10aa2be5beedd3a
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.xz

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

PKG_FIXUP:=autoreconf
PKG_BUILD_PARALLEL:=1	

include $(INCLUDE_DIR)/package.mk

#TARGET_CFLAGS := -D_DEFAULT_SOURCE
#TARGET_CXXFLAGS := -D_DEFAULT_SOURCE

define Package/lnav/Default
	SECTION:=net
	CATEGORY:=Network
	TITLE:=Lightweight Secured Socks5 Proxy
	URL:=https://github.com/tstack/lnav
	DEPENDS:=+libsqlite3 +libpcre +bzip2 +libcurl +libopenssl +libevent2 +libpthread +libncurses +libreadline +libstdcpp +zlib +libgmp
endef

Package/lnav = $(Package/lnav/Default)

define Package/lnav/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/lnav $(1)/usr/bin
endef

$(eval $(call BuildPackage,lnav))