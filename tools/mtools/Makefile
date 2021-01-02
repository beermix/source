# 
# Copyright (C) 2012-2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=mtools
PKG_VERSION:=4.0.26

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=@GNU/$(PKG_NAME)
PKG_HASH:=539f1c8b476a16e198d8bcb10a5799e22e69de49d854f7dbd85b64c2a45dea1a

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

HOST_CONFIGURE_ARGS += --without-x

HOST_CONFIGURE_VARS += \
	ac_cv_header_iconv_h=no

define Host/Compile
	$(MAKE) -C $(HOST_BUILD_DIR) mcopy mmd
endef

define Host/Install
	$(INSTALL_BIN) $(HOST_BUILD_DIR)/mcopy $(STAGING_DIR_HOST)/bin/
	$(INSTALL_BIN) $(HOST_BUILD_DIR)/mmd $(STAGING_DIR_HOST)/bin/
endef

define Host/Clean
	rm -f $(STAGING_DIR_HOST)/bin/mcopy
	rm -f $(STAGING_DIR_HOST)/bin/mmd
endef

$(eval $(call HostBuild))
