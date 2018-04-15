#
# Copyright (C) 2016 Daniel Golle <daniel@makrotopia.org>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=re2c
PKG_VERSION:=2.13.03

PKG_SOURCE_URL:=https://github.com/skvadrik/re2c/releases/download/{$PKG_VERSION}/
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_HASH:=

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/toolchain-build.mk

$(eval $(call HostBuild))
