#
# Copyright (C) 2014-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=fio
PKG_VERSION:=3.5
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=https://fossies.org/linux/misc

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/fio
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Flexible I/O Tester
  URL:=http://software.schmorp.de/pkg/fio.html
  DEPENDS:=+libpthread +librt +zlib
endef

define Package/fio/description
 A full-featured and high-performance event loop that is loosely modelled after
 fioent, but without its limitations and bugs.
endef

define Build/Configure
	(cd $(PKG_BUILD_DIR); \
		$(TARGET_CONFIGURE_OPTS) \
		./configure \
			--prefix=/usr \
			--cc=$(TARGET_CC) \
			--enable-lex \
			--cpu=$(ARCH) \
			--esx \
			--extra-cflags="$(TARGET_CFLAGS)" \
	);
endef

define Package/fio/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(CP) $(PKG_INSTALL_DIR)/usr/bin/fio $(1)/usr/bin/fio
endef

$(eval $(call BuildPackage,fio))
