#
# Copyright (C) 2009-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=gpm
PKG_VERSION:=4a93823

PKG_SOURCE_PROTO:=git
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_URL:=https://github.com/telmich/gpm
PKG_SOURCE_VERSION:=$(PKG_VERSION)

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=0
#PKG_FIXUP:=autoreconf

include $(INCLUDE_DIR)/package.mk

define Build/Prepare
	$(call Build/Prepare/Default)
	#cp $(PKG_BUILD_DIR)/configure.ac.footer $(PKG_BUILD_DIR)/configure.ac
	bash $(PKG_BUILD_DIR)/autogen.sh
endef

define Package/gpm
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Foreign Function Interface (FFI) library
  URL:=http://sourceware.org/gpm/
  MAINTAINER:=Peter Wagner <tripolar@gmx.at>
endef

define Package/gpm/description
  libgpm
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libgpm.{so*,a,la} \
		$(1)/usr/lib/
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/pkgconfig/* \
		$(1)/usr/lib/pkgconfig/
	$(SED) 's,includedir=.*,includedir=$$$${prefix}/include,' $(1)/usr/lib/pkgconfig/*.pc

	$(INSTALL_DIR) $(1)/usr/include
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/include/*.h \
		$(1)/usr/include/
endef

define Package/gpm/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/gpm.so.* \
		$(1)/usr/lib/
endef

$(eval $(call BuildPackage,gpm))
