#

include $(TOPDIR)/rules.mk

PKG_NAME:=nuttcp
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/nuttcp
	SECTION:=net
	CATEGORY:=Network
	TITLE:=nuttcp
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) $(TARGET_CONFIGURE_OPTS)
endef

define Package/nuttcp/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/nuttcp $(1)/usr/bin/nuttcp
endef

$(eval $(call BuildPackage,nuttcp))


