#
# Copyright (C) 2006-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=bandwhich
PKG_SOURCE_VERSION:=acd1b0a

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/imsnif/bandwhich

PKG_INSTALL:=1
HOST_BUILD_DEPENDS:=rust/host

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk
include ../rust/rustc-triple.mk

define Package/bandwhich/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/bandwhich $(1)/usr/bin/bandwhich
endef

$(eval $(call BuildPackage,bandwhich))
