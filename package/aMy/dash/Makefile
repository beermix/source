#
# Copyright (C) 2006-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=dash
PKG_VERSION:=0.5.10.2
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://gondor.apana.org.au/~herbert/dash
PKG_HASH:=3c663919dc5c66ec991da14c7cf7e0be8ad00f3db73986a987c118862b5f6071

PKG_BUILD_PARALLEL:=1
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/dash
  SECTION:=utils
  CATEGORY:=Utilities
  SUBMENU:=Shells
  TITLE:=dash
  DEPENDS:=+libedit
endef

define Package/dash/description
	dash (GNU zip) is a compression utility designed to be a \
	replacement for compress.
endef

CONFIGURE_VARS += \
	--exec-prefix="" \
	--with-libedit

define Package/bash/postinst
#!/bin/sh
grep -q bash "$${IPKG_INSTROOT}/etc/shells" || {
	echo /bin/dash >> "$${IPKG_INSTROOT}/etc/shells"
	echo /bin/sh >> "$${IPKG_INSTROOT}/etc/shells"
}
endef

define Package/bash/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/bin/dash $(1)/bin/
	$(LN) dash $(1)/bin/sh
endef

$(eval $(call BuildPackage,dash))
