#
# Copyright (C) 2014-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=sysbench
PKG_VERSION:=1.0.8

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/akopytov/sysbench.git
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
  DEPENDS:= +luajit
  TITLE:=Redirect any TCP connection to a SOCKS or HTTPS proxy server
endef

TARGET_CFLAGS += $(FPIC) -std=gnu99
HOST_CFLAGS += $(FPIC) -std=gnu99

CONFIGURE_ARGS += \
	--without-mysql \
	--with-system-luajit \
	--with-gcc-arch=i686 \
	
define Build/Compile
	$(MAKE) $(PKG_JOBS) -C $(PKG_BUILD_DIR) \
		HOST_CC="$(HOSTCC) $(HOST_CFLAGS) -m32" \
		CROSS="$(TARGET_CROSS)" \
		DPREFIX=$(PKG_INSTALL_DIR)/usr \
		DYNAMIC_CC="$(TARGET_CC) -fPIC" \
		TARGET_LD="$(TARGET_CC)" \
		TARGET_AR="$(TARGET_AR) rcus" \
		TARGET_STRIP=true \
		PREFIX=/usr \
		CFLAGS=
	rm -rf $(PKG_INSTALL_DIR)
	mkdir -p $(PKG_INSTALL_DIR)
	$(MAKE) -C $(PKG_BUILD_DIR) \
		DPREFIX=$(PKG_INSTALL_DIR)/usr \
		PREFIX=/usr \
		install
endef

define Package/sysbench/description
 Redsocks is a daemon running on the local system, that will transparently
 tunnel any TCP connection via a remote SOCKS4, SOCKS5 or HTTP proxy server. It
 uses the system firewall's redirection facility to intercept TCP connections,
 thus the redirection is system-wide, with fine-grained control, and does
 not depend on LD_PRELOAD libraries.
 
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
