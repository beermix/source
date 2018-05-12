#
# Copyright (C) 2014-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=sysbench
PKG_VERSION:=1.0.14

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/beermix/sysbench
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

PKG_FIXUP:=autoreconf
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/host-build.mk

define Package/sysbench
  SECTION:=net
  CATEGORY:=Network
#  DEPENDS:= +luajit +ck
  DEPENDS:=+libpthread
  TITLE:=Redirect any TCP connection to a SOCKS or HTTPS proxy server
endef

CONFIGURE_ARGS += \
	--without-mysql \
	--without-pgsql \
	--without-gcc-arch

define Package/sysbench/description
 sysbench is tests.
 
 Redsocks supports tunneling TCP connections and UDP packets. It has
 authentication support for both, SOCKS and HTTP proxies.
 
 Also included is a small DNS server returning answers with the "truncated" flag
 set for any UDP query, forcing the resolver to use TCP.
endef

define Package/sysbench/install
	$(INSTALL_DIR) $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/sysbench $(1)/usr/bin/
endef

$(eval $(call HostBuild,sysbench))
$(eval $(call BuildPackage,sysbench))
