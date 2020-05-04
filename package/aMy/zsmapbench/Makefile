#
# Copyright (C) 2016-2019 Jason A. Donenfeld <Jason@zx2c4.com>
# Copyright (C) 2016 Baptiste Jonglez <openwrt@bitsofnetworks.org>
# Copyright (C) 2016-2017 Dan Luedtke <mail@danrl.com>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information. https://git.zx2c4.com/zsmapbench-linux-compat/

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

define Package/zsmapbench/Default
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=VPN
  URL:=https://www.zsmapbench.com
  MAINTAINER:=Jason A. Donenfeld <Jason@zx2c4.com>
endef

define Package/zsmapbench/Default/description
  zsmapbench is a novel VPN that runs inside the Linux Kernel and utilizes
  state-of-the-art cryptography. It aims to be faster, simpler, leaner, and
  more useful than IPSec, while avoiding the massive headache. It intends to
  be considerably more performant than OpenVPN.  zsmapbench is designed as a
  general purpose VPN for running on embedded interfaces and super computers
  alike, fit for many different circumstances. It uses UDP.
endef

define Package/zsmapbench
  $(call Package/zsmapbench/Default)
  TITLE:=zsmapbench meta-package
  DEPENDS:=+zsmapbench-tools +kmod-zsmapbench +kmod-crypto-manager +kmod-fou
endef

include $(INCLUDE_DIR)/kernel-defaults.mk
include $(INCLUDE_DIR)/package-defaults.mk

define Build/Compile
	$(MAKE) $(KERNEL_MAKEOPTS) M="$(PKG_BUILD_DIR)/src" modules
endef

define Package/zsmapbench/install
  true
endef

define Package/zsmapbench/description
  $(call Package/zsmapbench/Default/description)
endef

define KernelPackage/zsmapbench
  SECTION:=kernel
  CATEGORY:=Kernel modules
  SUBMENU:=Network Support
  TITLE:=zsmapbench kernel module
  DEPENDS:=+IPV6:kmod-udptunnel6 +kmod-udptunnel4
  FILES:= $(PKG_BUILD_DIR)/src/zsmapbench.$(LINUX_KMOD_SUFFIX)
  AUTOLOAD:=$(call AutoProbe,zsmapbench)
endef

define KernelPackage/zsmapbench/description
  $(call Package/zsmapbench/Default/description)

  This package provides the kernel module for zsmapbench.
endef

$(eval $(call BuildPackage,zsmapbench))
$(eval $(call KernelPackage,zsmapbench))
