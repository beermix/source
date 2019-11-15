#
# Copyright (C) 2006-2019 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Profile/Generic
  NAME:=Generic x86
  PACKAGES:=kmod-igb kmod-bnx2 \
	kmod-pcnet32 kmod-8139too kmod-r8169
endef

define Profile/Generic/Description
	Generic Profile for x86 architecture
endef
$(eval $(call Profile,Generic))
