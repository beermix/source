#
# Copyright (C) 2014-2017 Jian Chang <aa65535@live.com>
#
# This is free software, licensed under the GNU General Public License v3.
# See /LICENSE for more information. +libbsd
#
include $(TOPDIR)/rules.mk

PKG_NAME:=lnav

#PKG_VERSION:=0.8.5
#PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
#PKG_SOURCE_URL:=https://github.com/tstack/lnav/releases/download/v$(PKG_VERSION)

PKG_VERSION:=56a341f
#PKG_VERSION:=73e902f
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/tstack/lnav.git
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

PKG_FIXUP:=autoreconf
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

#TARGET_CFLAGS := $(filter-out -O%,$(TARGET_CFLAGS)) -Os
TARGET_CFLAGS += -ffunction-sections -fdata-sections -flto
TARGET_CXXFLAGS += -ffunction-sections -fdata-sections -flto
TARGET_LDFLAGS += -Wl,--gc-sections

CONFIGURE_ARGS += --disable-silent-rules --disable-static

Package/lnav = $(Package/lnav/Default)
define Package/lnav/Default
	SECTION:=utils
	CATEGORY:=Utilities
	TITLE:=lnav
	URL:=https://github.com/tstack/lnav
	DEPENDS:=+libpthread +libstdcpp +librt +libncurses +libreadline \
	+zlib +libsqlite3 +libpcre +libpcrecpp +libbz2 +libcurl +libopenssl \
	+libidn2 +libnghttp2
endef

define Package/lnav/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/lnav $(1)/usr/bin
endef

$(eval $(call BuildPackage,lnav))
