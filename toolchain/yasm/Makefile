#
# Copyright (C) 2016 Daniel Golle <daniel@makrotopia.org>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=yasm
PKG_VERSION:=ea8f239
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/yasm/yasm
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/toolchain-build.mk
include $(INCLUDE_DIR)/cmake.mk

CMAKE_OPTIONS += \
	-DCMAKE_BUILD_TYPE=Release \
	-DENABLE_NLS=OFF \
	-DBUILD_SHARED_LIBS=OFF

define Host/Install
	$(MAKE) -C $(HOST_BUILD_DIR) \
		prefix=$(TOOLCHAIN_DIR) \
		install
endef

define Host/Clean
	rm -rf \
		$(HOST_BUILD_DIR) \
		$(BUILD_DIR_TOOLCHAIN)/$(PKG_NAME)
endef

$(eval $(call HostBuild))
