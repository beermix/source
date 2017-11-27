#
# Copyright (C) 2016-2017 LEDE project
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libressl
PKG_VERSION:=2.5.5
PKG_HASH:=e57f5e3d5842a81fe9351b6e817fcaf0a749ca4ef35a91465edba9e071dce7c4
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://mirror.ox.ac.uk/pub/OpenBSD/LibreSSL \
	http://ftp.jaist.ac.jp/pub/OpenBSD/LibreSSL \
	http://ftp.openbsd.org/pub/OpenBSD/LibreSSL

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

HOST_CONFIGURE_ARGS += --disable-shared \
			  --disable-hardening \
			  --enable-silent-rules
HOST_CFLAGS += $(FPIC)

$(eval $(call HostBuild))
