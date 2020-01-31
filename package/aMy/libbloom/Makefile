#
# Copyright (C) 2011-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libbloom
PKG_VERSION:=v1.6

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/jvirkki/libbloom
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/libbloom/Default
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=libbloom
  DEPENDS:=+check
endef

define Package/libbloom/Default/description
endef

define Package/libbloom
  $(call Package/libbloom/Default)
  TITLE+= libbloom
endef

define Package/libbloom/description
	$(call Package/libbloom/Default/description)
endef

$(eval $(call BuildPackage,libbloom))
