#
# Copyright (C) 2020 Jo-Philipp Wich <jo@mein.io>
#

include $(TOPDIR)/rules.mk

PKG_NAME:=firewall4
PKG_RELEASE:=1
PKG_MAINTAINER:=Jo-Philipp Wich <jo@mein.io>
PKG_LICENSE:=ISC

PKG_CONFIG_DEPENDS := CONFIG_IPV6

include $(INCLUDE_DIR)/package.mk

define Package/firewall4
  SECTION:=net
  CATEGORY:=Base system
  TITLE:=OpenWrt 4th gen firewall
  DEPENDS:=+utpl +utpl-mod-fs +utpl-mod-uci +utpl-mod-ubus +kmod-nft-core +kmod-nft-fib +kmod-nft-nat +kmod-nft-nat6 +nftables-json
  PKGARCH:=all
endef

define Package/firewall4/description
 This package provides a nftables-compatible implementation of the UCI firewall.
endef

define Package/firewall4/conffiles
/etc/config/firewall4
endef

define Build/Compile
endef

define Build/Prepare
endef

define Package/firewall4/install
	$(CP) -a ./files/* $(1)/
endef

$(eval $(call BuildPackage,firewall4))
