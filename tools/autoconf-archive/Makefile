#
# Copyright (C) 2009-2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=autoconf-archive
# PKG_VERSION:=2019.01.06
PKG_VERSION:=2017.09.28

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=@GNU/autoconf-archive
# PKG_HASH:=17195c833098da79de5778ee90948f4c5d90ed1a0cf8391b4ab348e2ec511e3f
PKG_HASH:=5c9fb5845b38b28982a3ef12836f76b35f46799ef4a2e46b48e2bd3c6182fa01

include $(INCLUDE_DIR)/host-build.mk

define Host/Install
	$(Host/Install/Default)
	rm -f $(STAGING_DIR_HOST)/share/aclocal/ax_prog_cc_for_build.m4
endef

$(eval $(call HostBuild))
