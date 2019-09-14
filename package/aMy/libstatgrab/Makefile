#
# Copyright (C) 2014-2015 OpenWrt.org
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libstatgrab
PKG_VERSION:=fa7e1d9

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/tdb/libstatgrab
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

PKG_MAINTAINER:=Felix Fietkau <nbd@nbd.name>
PKG_LICENSE:=LGPL-2.1+

include $(INCLUDE_DIR)/package.mk

define Package/libstatgrab
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Configuration File Library
  URL:=http://www.hyperrealm.com/libstatgrab/
  ABI_VERSION:=11
endef

CONFIGURE_ARGS += \
	--disable-examples \
	--disable-manpages \
	--disable-setuid-binaries \
	--disable-man-build

define Build/InstallDev
	$(CP) $(PKG_INSTALL_DIR)/* $(1)/
endef

define Package/libstatgrab/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libstatgrab.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libstatgrab))
