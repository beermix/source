#
# Copyright (C) 2014-2017 Jian Chang <aa65535@live.com>
#
# This is free software, licensed under the GNU General Public License v3.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=zstd
PKG_VERSION:=v1.3.3

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/facebook/zstd
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.xz

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/zstd/Default
	SECTION:=net
	CATEGORY:=Network
	TITLE:=Lightweight Secured Socks5 Proxy
	URL:=https://github.com/facebook/zstd
	DEPENDS:= +libpthread +librt +zlib +lzma
endef

TARGET_CFLAGS := -D_DEFAULT_SOURCE
TARGET_CXXFLAGS := -D_DEFAULT_SOURCE -std=gnu++14

Package/zstd = $(Package/zstd/Default)

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) CC="$(TARGET_CC)" CFLAGS="$(TARGET_CFLAGS)" LDFLAGS="$(TARGET_LDFLAGS)" HAVE_THREAD=1 HAVE_ZLIB=1 HAVE_LZMA=1 zstd
endef

define Package/zstd/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/zstd $(1)/usr/bin
endef


$(eval $(call BuildPackage,zstd))
