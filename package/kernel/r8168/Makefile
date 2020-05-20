#
# Copyright (C) 2008 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
# https://github.com/mtorromeo/r8168
# https://salsa.debian.org/debian/r8168.git


include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=r8168
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define KernelPackage/r8168
  SUBMENU:=Network Devices
  TITLE:=RealTek RTL-8168 PCI Gigabit Ethernet Adapter kernel support
  DEPENDS:=@PCI_SUPPORT +kmod-mii +r8169-firmware +LINUX_4_19:kmod-phy-realtek
  FILES:=$(PKG_BUILD_DIR)/r8168.ko
 AUTOLOAD:=$(call AutoProbe,r8168)
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
