#
# Copyright (C) 2006-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=miniupnpd
PKG_VERSION:=2.1
PKG_RELEASE:=2

PKG_SOURCE_URL:=http://miniupnp.free.fr/files
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_HASH:=

PKG_LICENSE:=BSD-3-Clause

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/version.mk

define Package/miniupnpd
  SECTION:=net
  CATEGORY:=Network
  DEPENDS:=+iptables +libip4tc +IPV6:libip6tc +IPV6:ip6tables +libuuid
  TITLE:=Lightweight UPnP IGD, NAT-PMP & PCP daemon
  SUBMENU:=Firewall
  URL:=http://miniupnp.free.fr/
endef

define Package/miniupnpd/conffiles
/etc/config/upnpd
endef

define Build/Prepare
	$(call Build/Prepare/Default)
	echo "$(VERSION_NUMBER)" | tr '() ' '_' >$(PKG_BUILD_DIR)/os.openwrt
	sed -i -e "s#^CFLAGS = .*-D#CPPFLAGS += -I/usr/include -D#" -e '/^CFLAGS :=/s/CFLAGS/CPPFLAGS/g' -e "s/#CFLAGS += -ansi/##CFLAGS += -ansi/g" -e "s/LIBS = -lip4tc/LIBS = -lip4tc/g" -e 's///' -e "s/-m /-m /g" $(PKG_BUILD_DIR)/Makefile.linux
	sed -i -e 's/\(strncpy(\([->a-z.]\+\), "[a-zA-Z]\+", \)IPT_FUNCTION_MAXNAMELEN);/\1sizeof(\2));/' $(PKG_BUILD_DIR)/netfilter/iptcrdr.c
endef

TARGET_CFLAGS += $(FPIC) -flto
TARGET_LDFLAGS += -Wl,--gc-sections,--as-needed

MAKE_FLAGS += \
	TARGET_OPENWRT=1 TEST=0 LIBS="" \
	CC="$(TARGET_CC) -DIPTABLES_143 -lip4tc -luuid \
		$(if $(CONFIG_IPV6),-lip6tc)" \
	CONFIG_OPTIONS="--portinuse --leasefile --igd2 \
		$(if $(CONFIG_IPV6),--ipv6)" \
	-f Makefile.linux miniupnpd

define Package/miniupnpd/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DIR) $(1)/etc/hotplug.d/iface
	$(INSTALL_DIR) $(1)/etc/uci-defaults
	$(INSTALL_DIR) $(1)/usr/share/miniupnpd

	$(INSTALL_BIN) $(PKG_BUILD_DIR)/miniupnpd $(1)/usr/sbin/miniupnpd
	$(INSTALL_BIN) ./files/miniupnpd.init $(1)/etc/init.d/miniupnpd
	$(INSTALL_CONF) ./files/upnpd.config $(1)/etc/config/upnpd
	$(INSTALL_DATA) ./files/miniupnpd.hotplug $(1)/etc/hotplug.d/iface/50-miniupnpd
	$(INSTALL_BIN) ./files/miniupnpd.defaults $(1)/etc/uci-defaults/99-miniupnpd
	$(INSTALL_DATA) ./files/firewall.include $(1)/usr/share/miniupnpd/firewall.include
endef

$(eval $(call BuildPackage,miniupnpd))
