#

include $(TOPDIR)/rules.mk

PKG_NAME:=liblz4
PKG_VERSION:=v1.8.2
PKG_RELEASE:=2

PKG_LICENSE:=BSD-2-Clause
PKG_MAINTAINER:=Darik Horn <dajhorn@vanadac.com>

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_PROTO:=git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_URL:=https://github.com/lz4/lz4.git
PKG_SOURCE_VERSION:=$(PKG_VERSION)

define Package/liblz4
	SECTION:=libs
	CATEGORY:=Libraries
	TITLE:=Extremely fast compression
	URL:=http://www.lz4.org/
endef

define Package/liblz4/description
  LZ4 is a compression codec that features a very fast encoder and an
  even faster decoder. This package provides the liblz4 shared library.
endef

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

export CMAKE_SOURCE_DIR=$(PKG_INSTALL_DIR)/../contrib/cmake_unofficial

CMAKE_OPTIONS += \
	-DCMAKE_BUILD_TYPE=Release \
	-DBUILD_SHARED_LIBS=1 \
	-DCMAKE_POSITION_INDEPENDENT_CODE=1 \

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/
	$(CP) -r -i $(PKG_INSTALL_DIR)/usr/* $(1)/usr/
endef

define Package/liblz4/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/liblz4.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,liblz4))