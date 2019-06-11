#
# Copyright (C) 2014-2015 OpenWrt.org
#

include $(TOPDIR)/rules.mk

PKG_NAME:=bwm-ng
PKG_VERSION:=059e028

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/vgropp/bwm-ng
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/bwm-ng
  SECTION:=net
  CATEGORY:=Network
  DEPENDS:=+BWMNG_LIBNCURSES:libncurses
  TITLE:=bwm-ng
  URL:=http://www.gropp.org/?id=projects&sub=bwm-ng
  MENU:=1
endef

define Package/bwm-ng/description
  Bandwidth Monitor NG is a small and simple console-based live
  network and disk io bandwidth monitor.
endef

define Package/bwm-ng/config
  source "$(SOURCE)/Config.in"
endef

define Build/Configure
	$(call Build/Configure/Default, \
	$(if $(CONFIG_BWMNG_CONFIGFILE),--enable,--disable)-configfile \
	$(if $(CONFIG_BWMNG_HTML),--enable,--disable)-html \
	$(if $(CONFIG_BWMNG_CSV),--enable,--disable)-csv \
	$(if $(CONFIG_BWMNG_EXTENDEDSTATS),--enable,--disable)-extendedstats \
	$(if $(CONFIG_BWMNG_LIBNCURSES),--with,--without)-ncurses \
	$(if $(CONFIG_BWMNG_TIME),--with,--without)-time \
	$(if $(CONFIG_BWMNG_GETOPT_LONG),--with,--without)-getopt_long \
	--with-strip \
	--with-procnetdev \
	--with-diskstats \
	)
endef

define Package/bwm-ng/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/bwm-ng $(1)/usr/bin/
endef

$(eval $(call BuildPackage,bwm-ng))
