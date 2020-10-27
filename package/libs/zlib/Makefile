#
# Copyright (C) 2006-2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=zlib
PKG_VERSION:=1.9.9-b1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/zlib-ng/zlib-ng.git
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

PKG_CONFIG_DEPENDS:= CONFIG_ZLIB_OPTIMIZE_SPEED

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/zlib
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Library implementing the deflate compression method
  URL:=http://www.zlib.net/
endef

define Package/zlib-dev
  SECTION:=devel
  CATEGORY:=Development
  SUBMENU:=Libraries
  DEPENDS:=zlib
  TITLE:=Development files for the zlib library
endef

define Package/zlib/description
 zlib is a lossless data-compression library.
 This package includes the shared library.
endef

define Package/zlib-dev/description
 zlib is a lossless data-compression library.
 This package includes the development support files.
endef

define Package/zlib/config
	source "$(SOURCE)/Config.in"
endef

TARGET_CFLAGS += $(FPIC)

ifeq ($(CONFIG_ZLIB_OPTIMIZE_SPEED),y)
	TARGET_CFLAGS := -O3 $(filter-out -fno-caller-saves -O%,$(TARGET_CFLAGS))
endif

CMAKE_OPTIONS += \
	-DCMAKE_VERBOSE_MAKEFILE=1 \
	-DWITH_GZFILEOP=1 \
	-DZLIB_COMPAT=1 \
	-DWITH_OPTIM=1 \
	-DWITH_NEW_STRATEGIES=1 \
	-DZLIB_ENABLE_TESTS=0 \
	-DWITH_AVX2=0 \
	-DWITH_SSE2=1 \
	-DWITH_SSE4=0 \
	-DWITH_PCLMULQDQ=0 \
	-DWITH_NEON=0 \
	-DWITH_POWER8=0

define Build/InstallDev
	mkdir -p $(1)/usr/include
	$(CP)	$(PKG_INSTALL_DIR)/usr/include/z{conf,lib}.h \
		$(1)/usr/include/
	mkdir -p $(1)/usr/lib
	$(CP)	$(PKG_INSTALL_DIR)/usr/lib/libz.{a,so*} \
		$(1)/usr/lib/
	mkdir -p $(1)/usr/lib/pkgconfig
	$(CP)	$(PKG_INSTALL_DIR)/usr/lib/pkgconfig/zlib.pc \
		$(1)/usr/lib/pkgconfig/
endef

# libz.so is needed for openssl (zlib-dynamic)
define Package/zlib/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libz.so $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libz.so.* $(1)/usr/lib/
endef

define Package/zlib-dev/install
	$(INSTALL_DIR) $(1)/usr/include
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/include/zconf.h \
	  $(1)/usr/include/
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/include/zlib.h \
	  $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libz.a $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/zlib.pc \
	  $(1)/usr/lib/pkgconfig/
endef

$(eval $(call BuildPackage,zlib))
$(eval $(call BuildPackage,zlib-dev))
