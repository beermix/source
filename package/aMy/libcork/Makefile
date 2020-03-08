#
# Copyright (C) 2011-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libcork
PKG_VERSION:=fb35659
PKG_RELEASE:=1

PKG_SOURCE_URL:=https://github.com/rogers0/libcork.git
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_SOURCE_VERSION).tar.gz

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libcork
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=libcork
  DEPENDS:=+libpthread +librt +check
endef

define Build/Prepare
	$(call Build/Prepare/Default)
	rm -f obj-*/docs/old/html/.buildinfo
	sed -i " \
		s%http[s]*://cdn.mathjax.org/mathjax/latest/MathJax.js%file:///usr/share/javascript/mathjax/MathJax.js%; \
		s%https://cdnjs.cloudflare.com/ajax/libs/mathjax/[0-9].[0-9].[0-9]/MathJax.js%file:///usr/share/javascript/mathjax/MathJax.js%" \
		obj-*/docs/old/html/*.html
endef

CMAKE_OPTIONS += \
	-DCMAKE_BUILD_TYPE=Release \
	-DENABLE_STATIC=OFF
	
define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/libcork $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/include/libcork/* $(1)/usr/include/libcork/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/src/libcork.pc $(1)/usr/lib/pkgconfig
endef

define Package/libcork/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libcork.so.* $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/bin
	#$(CP) $(PKG_INSTALL_DIR)/usr/bin/cork-hash $(1)/usr/bin/
endef

$(eval $(call BuildPackage,libcork))
