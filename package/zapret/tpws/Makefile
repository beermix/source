#

include $(TOPDIR)/rules.mk

PKG_NAME:=tpws
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/tpws
	SECTION:=net
	CATEGORY:=Network
	TITLE:=tpws
	SUBMENU:=Zapret
 	DEPENDS:=+zlib +libcap +iptables-mod-extra +iptables-mod-nfqueue +iptables-mod-filter +iptables-mod-ipopt +iptables-mod-conntrack-extra +iptables-mod-tproxy
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./tpws/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) $(TARGET_CONFIGURE_OPTS)
endef

define Package/tpws/install
	$(INSTALL_DIR) $(1)/opt/zapret/tpws
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/tpws $(1)/opt/zapret/tpws
endef

$(eval $(call BuildPackage,tpws))

