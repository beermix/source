# SPDX-License-Identifier: GPL-2.0-or-later
#
# Copyright (C) 2020 Paul Spooren <mail@aparcar.org>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=yaml
PKG_VERSION:=0.2.5
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://pyyaml.org/download/libyaml/
PKG_HASH:=c642ae9b75fee120b2d96c712538bd2cf283228d2337df2cf2988e3c02678ef4

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=COPYING
PKG_CPE_ID:=cpe:/a:pyyaml_project:pyyaml

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

define Host/Install
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(HOST_BUILD_DIR)/include/yaml.h $(STAGING_DIR_HOST)/include/
	$(CP) $(HOST_BUILD_DIR)/src/.libs/libyaml*.{a,so*} $(STAGING_DIR_HOST)/lib/
	$(CP) $(HOST_BUILD_DIR)/yaml*.pc $(STAGING_DIR_HOST)/lib/pkgconfig/
endef

define Host/Clean
	rm -f $(STAGING_DIR_HOST)/include/yaml.h
	rm -f $(STAGING_DIR_HOST)/lib/libyaml*.{a,so*}
	rm -f $(STAGING_DIR_HOST)/lib/pkgconfig/yaml*.pc
	$(call Host/Clean/Default)
endef

$(eval $(call HostBuild))
