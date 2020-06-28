#
# Copyright (C) 2008-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=bison
PKG_VERSION:=3.6.4

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=@GNU/$(PKG_NAME)
PKG_HASH:=8b13473b31ca7fcf65e5e8a74224368ffd5df19275602a9c9567ba393f18577d

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

HOST_CONFIGURE_ARGS += --enable-threads=posix --disable-nls

define Host/Clean
	-$(MAKE) -C $(HOST_BUILD_DIR) uninstall
	$(call Host/Clean/Default)
endef

define Host/Install
	$(call Host/Install/Default)
	$(INSTALL_BIN) ./scripts/yacc $(STAGING_DIR_HOST)/bin/yacc
endef

$(eval $(call HostBuild))
