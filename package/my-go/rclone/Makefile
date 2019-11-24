#
# Copyright (C) 2011-2016 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=rclone
PKG_VERSION:=v1.40
PKG_RELEASE:=1
PKG_GOGET:=github.com/ncw/rclone

GOPKG_SOURCE=GO_$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE).tar.xz

#!!! uncomment PKG_SOURCE to download fixed version
PKG_SOURCE=$(GOPKG_SOURCE)
PKG_COMMIT=$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/golang.mk

define Package/rclone
	$(call Package/gopackage/Default)
	TITLE:=rclone is a simple command line tool that turns your CLI tools into web applications.
	URL:=https://github.com/ncw/rclone
	DEPENDS:=+libgo
endef

define Package/rclone/description
 rclone - Share your terminal as a web application.
endef

define Package/rclone/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/$(PKG_NAME) $(1)/usr/bin
endef

$(eval $(call BuildPackage,rclone))
