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
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./tpws/* $(PKG_BUILD_DIR)/
endef

TARGET_CFLAGS += -O3

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) $(TARGET_CONFIGURE_OPTS)
endef

define Package/tpws/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/tpws $(1)/usr/bin/
endef

$(eval $(call BuildPackage,tpws))

