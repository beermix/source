#
# Copyright (C) 2006-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=gawk
PKG_VERSION:=4.2.1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_HASH:=d1119785e746d46a8209d28b2de404a57f983aa48670f4e225531d3bdc175551
PKG_SOURCE_URL:=https://ftp.gnu.org/gnu/gawk

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

HOST_CONFIGURE_ARGS += \
	--without-libsigsegv

define Host/Install
	$(MAKE) -C $(HOST_BUILD_DIR) install
endef

$(eval $(call HostBuild))
