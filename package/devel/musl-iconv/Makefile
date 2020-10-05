#

include $(TOPDIR)/rules.mk

PKG_NAME:=musl-iconv
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/musl-iconv
  SECTION:=devel
  CATEGORY:=Development
  TITLE:=musl-iconv
  DEPENDS:=
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) $(TARGET_CONFIGURE_OPTS)
endef

define Package/musl-iconv/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/musl-iconv $(1)/usr/bin/iconv
endef

$(eval $(call BuildPackage,musl-iconv))

