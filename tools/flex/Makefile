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

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/westes/flex/archive/v$(PKG_VERSION)/
PKG_HASH:=cde6e46064a941a3810f7bbc612a2c39cb3aa29ce7eb775089c2515d0adfa7e9

HOST_FIXUP:=autoreconf
HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

HOST_CONFIGURE_ARGS += ac_cv_func_realloc_0_nonnull=yes ac_cv_func_malloc_0_nonnull=yes --disable-shared

define Host/Install
	$(call Host/Install/Default)
	$(LN) flex $(STAGING_DIR_HOST)/bin/lex
endef

define Host/Clean
	-$(MAKE) -C $(HOST_BUILD_DIR) uninstall
	$(call Host/Clean/Default)
endef

$(eval $(call HostBuild))
