#
# Copyright (C) 2014-2017 Jian Chang <aa65535@live.com>
#
# This is free software, licensed under the GNU General Public License v3.
# See /LICENSE for more information. +libbsd
#
include $(TOPDIR)/rules.mk

PKG_NAME:=lnav

#PKG_VERSION:=0.9.0
#PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
#PKG_SOURCE_URL:=https://github.com/tstack/lnav/releases/download/v$(PKG_VERSION)

PKG_SOURCE_VERSION:=v0.9.0
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/tstack/lnav.git

PKG_FIXUP:=autoreconf
PKG_BUILD_PARALLEL:=1

#include $(INCLUDE_DIR)/uclibc++.mk
include $(INCLUDE_DIR)/package.mk

#include $(INCLUDE_DIR)/cmake.mk
#CMAKE_SOURCE_SUBDIR:=src

#TARGET_CFLAGS := $(filter-out -O%,$(TARGET_CFLAGS)) -Os
#TARGET_CFLAGS += -ffunction-sections -fdata-sections -flto
#TARGET_CXXFLAGS += -ffunction-sections -fdata-sections -flto
#TARGET_LDFLAGS += -Wl,--gc-sections  --disable-static
#export LDFLAGS="-Wl,--copy-dt-needed-entries"

#TARGET_CFLAGS += -static -no-pie
#TARGET_CXXFLAGS += -static -U__unused -no-pie
#TARGET_LDFLAGS += -L$(STAGING_DIR)/lib
#TARGET_CPPFLAGS  += -I$(STAGING_DIR)/include

#TARGET_LDFLAGS += -Wl,-O1,--sort-common,--as-needed

CONFIGURE_ARGS += --disable-silent-rules # --disable-static


Package/lnav = $(Package/lnav/Default)
define Package/lnav/Default
	SECTION:=utils
	CATEGORY:=Utilities
	TITLE:=lnav
	URL:=https://github.com/tstack/lnav
	DEPENDS:=+libpthread +libstdcpp +librt +libncurses +libreadline \
	+zlib +libpcre +libpcrecpp +libbz2 +libcurl +libopenssl +libsqlite3 +libarchive
endef

define Package/lnav/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/lnav $(1)/usr/bin
endef

$(eval $(call BuildPackage,lnav))
