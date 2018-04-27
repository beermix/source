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

PKG_BUILD_PARALLEL:=1
PKG_INSTALL:=1
PKG_USE_MIPS16:=0

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

CMAKE_BINARY_DIR=$(PKG_BUILD_DIR)/build

CMAKE_OPTIONS += \
	-DBUILD_DRIVER=0 \
	-DBUILD_LIBSCAP_EXAMPLES=0 \
	-DENABLE_DKMS=0 \
	-DUSE_BUNDLED_CURL=1 \
	-DUSE_BUNDLED_NCURSES=1 \
	-DUSE_BUNDLED_OPENSSL=1 \
	-DUSE_BUNDLED_ZLIB=1 \
	-DDCMAKE_BUILD_TYPE=Release \
	-DCMAKE_SHARED_LDFLAGS:=-Wl,-Bsymbolic-functions
	
define Package/sysdig
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE+= (utilities)
  URL:=http://www.gropp.org/?id=projects&sub=sysdig
  MENU:=1
  DEPENDS:=+libpthread
endef

define Build/Compile
	+$(MAKE) $(PKG_JOBS) -C $(PKG_BUILD_DIR)/build
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
