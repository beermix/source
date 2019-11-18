#
# Copyright (C) 2014-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=sysbench
PKG_VERSION:=1.0.18

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/akopytov/sysbench
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

PKG_FIXUP:=autoreconf
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/host-build.mk

define Package/sysbench
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:=+libpthread +luajit
  TITLE:=sysbench is a scriptable multi-threaded benchmark tool based on LuaJIT
endef

CONFIGURE_ARGS += \
	--without-mysql \
	--without-pgsql \
	--disable-shared \
	--with-system-luajit

define Package/sysbench/install
	$(INSTALL_DIR) $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/sysbench $(1)/usr/bin/
endef

$(eval $(call HostBuild,sysbench))
$(eval $(call BuildPackage,sysbench))
