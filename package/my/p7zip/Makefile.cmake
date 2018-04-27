#
# Copyright (C) 2011-2017 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=p7zip
PKG_VERSION:=16.02

PKG_SOURCE:=$(PKG_NAME)_$(PKG_VERSION)_src_all.tar.bz2
PKG_SOURCE_URL:=@SF/p7zip/p7zip/$(PKG_VERSION)
PKG_MD5SUM:=a0128d661cfe7cc8c121e73519c54fbf

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)_$(PKG_VERSION)

PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

export CMAKE_SOURCE_DIR=$(PKG_INSTALL_DIR)/../CPP/7zip/CMAKE/
export CMAKE_BINARY_DIR=$(PKG_INSTALL_DIR)/../CPP/7zip/CMAKE/

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release

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
