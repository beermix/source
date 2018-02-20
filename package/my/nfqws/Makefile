#

include $(TOPDIR)/rules.mk

PKG_NAME:=nfqws
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/nfqws
	SECTION:=net
	CATEGORY:=Network
	TITLE:=nfqws
	SUBMENU:=Zapret
 	DEPENDS:=+libnetfilter-queue
endef

TARGET_CFLAGS += -O3

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./nfq/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) $(TARGET_CONFIGURE_OPTS)
endef

define Package/nfqws/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/nfqws $(1)/usr/bin/
endef

$(eval $(call BuildPackage,nfqws))


