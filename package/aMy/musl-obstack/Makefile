#
# Copyright (C) 2014-2015 OpenWrt.org
#

include $(TOPDIR)/rules.mk

PKG_NAME:=musl-obstack
PKG_SOURCE_VERSION:=v1.1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/pullmoll/musl-obstack

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

PKG_MAINTAINER:=Felix Fietkau <nbd@nbd.name>
PKG_LICENSE:=LGPL-2.1+

include $(INCLUDE_DIR)/package.mk

define Package/musl-obstack
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=A standalone library to implement GNU libc's obstac
  ABI_VERSION:=11
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/obstack.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libobstack.{a,so*,la} $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/musl-obstack.pc $(1)/usr/lib/pkgconfig/
endef

define Package/musl-obstack/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libobstack.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,musl-obstack))
