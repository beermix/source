#
# Copyright (C) 2014-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=sysbench
PKG_VERSION:=1.0.13

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/akopytov/sysbench.git
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

PKG_FIXUP:=libtool
PKG_INSTALL:=1
PKG_FIXUP:=autoreconf
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/sysbench
  SECTION:=net
  CATEGORY:=Network
  DEPENDS:=+libpthread +librt +libatomic
  TITLE:=Redirect any TCP connection to a SOCKS or HTTPS proxy server
endef

TARGET_LDFLAGS+=-latomic
TARGET_CFLAGS += $(FPIC) -std=gnu99
HOST_CFLAGS += $(FPIC) -std=gnu99

ifeq ($(HOST_ARCH),x86_64)
  ifeq ($(CONFIG_x86_64),)
    HOST_BITS := -m32
  endif
endif

define Build/Compile
	$(MAKE) $(PKG_JOBS) -C $(PKG_BUILD_DIR) \
		HOST_CC="$(HOSTCC) $(HOST_CFLAGS) -m32" \
		CROSS="$(TARGET_CROSS)" \
		DPREFIX=$(PKG_INSTALL_DIR)/usr \
		PREFIX=/usr \
		CFLAGS="-m32 -march=bonnell --param=l1-cache-size=24 --param=l1-cache-line-size=64 --param=l2-cache-size=512 -O2 -pipe -fomit-frame-pointer"
	rm -rf $(PKG_INSTALL_DIR)
	mkdir -p $(PKG_INSTALL_DIR)
	$(MAKE) -C $(PKG_BUILD_DIR) \
		DPREFIX=$(PKG_INSTALL_DIR)/usr \
		PREFIX=/usr \
		install
endef

CONFIGURE_ARGS += \
	--without-mysql \
	--with-gcc-arch=i586 \
	
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

$(eval $(call BuildPackage,sysbench))
