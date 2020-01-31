#
# Copyright (C) 2011-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libcork
PKG_VERSION:=17bf6a2
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/dcreager/libcork
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

PKG_INSTALL:=1
PKG_FIXUP:=autoreconf
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/libcork/Default
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=libcork
  DEPENDS:=+check
endef

define Package/libcork/Default/description
endef

define Package/libcork
  $(call Package/libcork/Default)
  TITLE+= libcork
endef

define Package/libcork/description
	$(call Package/libcork/Default/description)
endef

$(eval $(call BuildPackage,libcork))