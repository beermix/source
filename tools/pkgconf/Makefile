# 
# Copyright (C) 2006-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=pkgconf
PKG_VERSION:=1.3.0

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://distfiles.dereferenced.org/pkgconf/

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

unexport PKG_CONFIG

HOST_CONFIGURE_ARGS += --disable-shared

ifeq ($(HOST_OS),Darwin)
HOST_LDFLAGS += -framework CoreFoundation -framework Carbon
endif

define Host/Install
	$(MAKE) -C $(HOST_BUILD_DIR) install
	ln -sf $(STAGING_DIR_HOST)/bin/pkgconf $(STAGING_DIR_HOST)/bin/pkg-config
	#$(INSTALL_BIN) ./files/pkg-config $(STAGING_DIR_HOST)/bin/pkg-config
endef

define Host/Clean
	-$(MAKE) -C $(HOST_BUILD_DIR) uninstall
	$(call Host/Clean/Default)
endef

$(eval $(call HostBuild))
