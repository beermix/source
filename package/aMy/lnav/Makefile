#
# Copyright (C) 2014-2017 Jian Chang <aa65535@live.com>
#
# This is free software, licensed under the GNU General Public License v3.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=lnav
PKG_VERSION:=0.8.5

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/tstack/lnav/releases/download/v$(PKG_VERSION)/

PKG_FIXUP:=autoreconf
PKG_BUILD_PARALLEL:=1

PKG_INSTALL:=1	

include $(INCLUDE_DIR)/uclibc++.mk
include $(INCLUDE_DIR)/package.mk

Package/lnav = $(Package/lnav/Default)

CONFIGURE_ARGS += \
	--enable-silent-rules \
	--disable-static \
	--disable-tinfo

define Package/lnav/Default
	SECTION:=utils
	CATEGORY:=Utilities
	TITLE:=lnav
	URL:=https://github.com/tstack/lnav
	DEPENDS:=+libpthread +libstdcpp +libncurses +libreadline +zlib +libsqlite3 +libpcre +libpcrecpp +libbz2 +libcurl +libopenssl  
endef

define Package/lnav/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/lnav $(1)/usr/bin
endef

$(eval $(call BuildPackage,lnav))