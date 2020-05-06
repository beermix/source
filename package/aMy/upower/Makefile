#
# Copyright (C) 2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=upower
PKG_VERSION:=d2917c0c71b2ee5cfd0e46e7401229a4c80ca0e3
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=git://anongit.freedesktop.org/upower
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

include $(INCLUDE_DIR)/package.mk

define Package/upower
  SUBMENU:=Filesystem
  SECTION:=utils
  CATEGORY:=Utilities
  #DEPENDS:=
  TITLE:=upower
endef

CONFIGURE_ARGS += --disable-gtk-doc

define Package/upower/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(CP) $(PKG_INSTALL_DIR)/usr/bin/* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,upower))
