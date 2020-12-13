#
# Copyright (C) 2014-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=nsd
PKG_VERSION:=4.3.4
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://www.nlnetlabs.nl/downloads/nsd
PKG_HASH:=3be834a97151a7ba8185e46bc37ff12c2f25f399755ae8a2d0e3711801528b50

PKG_MAINTAINER:=Vasilis Tsiligiannis <acinonyx@openwrt.gr>
PKG_LICENSE:=BSD-3-Clause
PKG_LICENSE_FILES:=LICENSE

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/nsd/default
  TITLE:=NSD Name Server Daemon
  URL:=https://www.nlnetlabs.nl/projects/nsd/
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=IP Addresses and Names
  USERID:=_nsd:_nsd
endef

define Package/nsd/default/description
  NSD is an authoritative only, high performance, simple and open source name
  server.
endef

define Package/nsd
  $(Package/nsd/default)
  TITLE += (with SSL support)
  DEPENDS += +libopenssl +libevent2
  VARIANT:=ssl
endef

define Package/nsd/description
  $(Package/nsd/default/description)
endef

define Package/nsd-checkconf/description
  $(Package/nsd/default/description)
endef

CONFIGURE_ARGS+= \
	--enable-packed \
	--enable-recvmmsg \
	--enable-tcp-fastopen \
	--disable-checking \
	--disable-ipv6 \
	--with-user="_nsd" \
	--with-libevent="$(STAGING_DIR)/usr" \
	--enable-root-server

#CONFIGURE_VARS+= \
#	ac_cv_c_va_list_def=no \
#	ac_cv_c_strptime_needs_defs=no

ifeq ($(BUILD_VARIANT),ssl)
	CONFIGURE_ARGS += --with-ssl="$(STAGING_DIR)/usr"
else
	CONFIGURE_ARGS += --without-ssl
endif

define Package/nsd/conffiles
/etc/nsd/
endef

define Package/nsd/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/{nsd,nsd-checkconf,nsd-checkzone,nsd-control,nsd-control-setup} $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/nsd
	$(INSTALL_CONF) $(PKG_INSTALL_DIR)/etc/nsd/nsd.conf.sample $(1)/etc/nsd/nsd.conf
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_DIR) $(1)/etc/nsd
	$(INSTALL_BIN) ./files/nsd.init $(1)/etc/init.d/nsd
	$(INSTALL_BIN) ./files/opennic.conf $(1)/etc/nsd/
endef

$(eval $(call BuildPackage,nsd))
