#
# Copyright (C) 2011-2017 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=p7zip
PKG_SOURCE_VERSION:=be1a54f
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/jinfeihan57/p7zip

PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
#include $(INCLUDE_DIR)/cmake.mk

#CMAKE_SOURCE_SUBDIR:=CPP/7zip/CMAKE

TARGET_CFLAGS:=-O3 $(filter-out -fno-caller-saves -O%,$(call qstrip,$(TARGET_CFLAGS)))

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) CC="$(TARGET_CC)" CXX="$(TARGET_CXX)" LDFLAGS="$(TARGET_LDFLAGS)" -j7
endef

define Package/p7zip
	SECTION:=utils
	CATEGORY:=Utilities
	SUBMENU:=Compression
	DEPENDS:=+libpthread +libstdcpp
	TITLE:=Command line version of 7-zip for POSIX systems
	URL:=http://p7zip.sourceforge.net
	MAINTAINER:=Entware team, http://entware.net
endef

define Package/p7zip/description
 Command line version of 7-zip for POSIX systems.
endef

define Package/p7zip/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/7za $(1)/usr/bin
endef

$(eval $(call BuildPackage,p7zip))
