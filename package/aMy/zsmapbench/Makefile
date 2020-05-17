#
# Copyright (C) 2016-2019 Jason A. Donenfeld <Jason@zx2c4.com>
# Copyright (C) 2016 Baptiste Jonglez <openwrt@bitsofnetworks.org>
# Copyright (C) 2016-2017 Dan Luedtke <mail@danrl.com>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=zsmapbench

PKG_VERSION:=f393ccd
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/sjenning/zsmapbench
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

# zsmapbench's makefile needs this to know where to build the kernel module
export KERNELDIR:=$(LINUX_DIR)

include $(INCLUDE_DIR)/package.mk

define Package/zsmapbench
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=zsmapbench
  DEPENDS:=
endef

include $(INCLUDE_DIR)/kernel-defaults.mk
include $(INCLUDE_DIR)/package-defaults.mk

define Build/Compile
	$(MAKE) $(KERNEL_MAKEOPTS) M="$(PKG_BUILD_DIR)/src" modules
endef

$(eval $(call BuildPackage,zsmapbench))
