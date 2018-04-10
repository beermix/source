#
# Copyright (C) 2006-2017 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.

#TODO
#
# * uClibcpp not supported, performance +100x slower. libstdcpp is being used. https://bugs.busybox.net/show_bug.cgi?id=2545
# * liblua is still not recognized/blindly accepted. Impossible to compile with support
#

include $(TOPDIR)/rules.mk

PKG_NAME:=nmap
PKG_VERSION:=7.70
PKG_RELEASE:=1
PKG_MAINTAINER:=Nuno Goncalves <nunojpg@gmail.com>

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=https://nmap.org/dist/
PKG_HASH:=847b068955f792f4cc247593aca6dc3dc4aae12976169873247488de147a6e18
PKG_LICENSE:=GPL-2.0
PKG_LICENSE_FILES:=COPYING

PKG_INSTALL:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(BUILD_VARIANT)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

NMAP_DEPENDS:=+libpcap +libstdcpp +zlib +libpcre
NCAT_DEPENDS:=+libpcap
NPING_DEPENDS:=+libpcap +libpthread +libstdcpp
NDIFF_DEPENDS:=+python

define Package/nmap/default
  SUBMENU:=NMAP Suite
  SECTION:=net
  CATEGORY:=Network
  URL:=http://nmap.org/
endef

define Package/nmap
$(call Package/nmap/default)
  DEPENDS:=$(NMAP_DEPENDS)
  VARIANT:=nossl
  TITLE:=Utility for network exploration or security auditing
endef

define Package/nmap-ssl
$(call Package/nmap/default)
  DEPENDS:=$(NMAP_DEPENDS) +libopenssl
  VARIANT:=ssl
  TITLE:=Nmap (with OpenSSL support)
endef
