#
# Copyright (C) 2014-2015 OpenWrt.org
#

include $(TOPDIR)/rules.mk

PKG_NAME:=sysdig
PKG_VERSION:=0.21.0

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/draios/sysdig
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

export CMAKE_BINARY_DIR=$(PKG_INSTALL_DIR)/../bin
export CMAKE_SOURCE_DIR=$(PKG_INSTALL_DIR)/../bin

define Package/sysdig
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE+= (utilities)
  URL:=http://www.gropp.org/?id=projects&sub=sysdig
  MENU:=1
  DEPENDS:=+libcurl +libpthread +libncurses +zlib
endef

define Package/sysdig/description
  Bandwidth Monitor NG is a small and simple console-based live
  network and disk io bandwidth monitor.
endef

define Package/sysdig/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/sysdig $(1)/usr/bin/
endef

$(eval $(call BuildPackage,sysdig))
