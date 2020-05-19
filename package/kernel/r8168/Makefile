#
# Copyright (C) 2008 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#


include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=r8168
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define KernelPackage/r8168
  SUBMENU:=$(NETWORK_DEVICES_MENU)
  TITLE:=Debian RTL-8169 PCI Driver
  DEPENDS:=@PCI_SUPPORT +kmod-mii +LINUX_4_19:kmod-phy-realtek
  FILES:=$(PKG_BUILD_DIR)/r8168.ko
 AUTOLOAD:=$(call AutoProbe,r8169)
endef

MAKE_OPTS:= \
	$(KERNEL_MAKE_FLAGS) \
	SUBDIRS="$(PKG_BUILD_DIR)"

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		$(MAKE_OPTS) \
		modules
endef

$(eval $(call KernelPackage,r8168))
