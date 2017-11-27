# 
# Copyright (C) 2006-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=go-bootstrap
PKG_VERSION:=1.4
PKG_REV:=4d5426a570c2820c5894a61b52e3dc147e4e7925
OS=$(shell uname | tr 'A-Z' 'a-z')
bintype:=$(shell uname -m | sed \
        -e 's/i[3-9]86/386/' \
        -e 's/x86_64/amd64/' \
)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_SUBDIR:=go-bootstrap-1.4
PKG_SOURCE_URL:=https://github.com/golang/go
PKG_SOURCE_PROTO:=git
PKG_SOURCE_VERSION:=$(PKG_REV)
HOST_BUILD_DIR:=$(STAGING_DIR_HOST)/go-bootstrap-1.4

include $(INCLUDE_DIR)/host-build.mk

#build go for all architetures - in case gccgo does not work

define Host/Compile
endef

define Host/Install
endef

define Host/Clean
	rm -rf $(STAGING_DIR_HOST)/go-bootstrap-1.4
endef

$(eval $(call HostBuild))
