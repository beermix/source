#
# Copyright (C) 2008-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=flex
PKG_CPE_ID:=cpe:/a:flex_project:flex
PKG_VERSION:=2.6.0

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=@SF/$(PKG_NAME)
PKG_HASH:=24e611ef5a4703a191012f80c1027dc9d12555183ce0ecd46f3636e587e9b8e9

HOST_FIXUP:=autoreconf
HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

HOST_CONFIGURE_ARGS += --disable-shared

define Host/Install
	$(call Host/Install/Default)
	$(LN) flex $(STAGING_DIR_HOST)/bin/lex
endef

define Host/Clean
	-$(MAKE) -C $(HOST_BUILD_DIR) uninstall
	$(call Host/Clean/Default)
endef

$(eval $(call HostBuild))
