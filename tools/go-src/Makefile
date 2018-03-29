# 
# Copyright (C) 2006-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=go-src
PKG_VERSION:=1.10.1

PKG_SOURCE:=go$(PKG_VERSION).src.tar.gz
PKG_SOURCE_URL:=https://storage.googleapis.com/golang
HOST_BUILD_DIR:=$(STAGING_DIR_HOST)/go
#PKG_HASH:=665F184BF8AC89986CFD5A4460736976F60B57DF6B320AD71AD4CEF53BB143DC

include $(INCLUDE_DIR)/host-build.mk

define Host/Compile
	(cd $(STAGING_DIR_HOST)/go/src ; \
		GOROOT_BOOTSTRAP=$(STAGING_DIR_HOST)/go1.4 GOOS=linux GOARCH=386 ./make.bash --no-clean ; \
	)
endef

define Host/Install
endef

define Host/Clean
	rm -rf $(STAGING_DIR_HOST)/go
endef

$(eval $(call HostBuild))
