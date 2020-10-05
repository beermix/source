#

include $(TOPDIR)/rules.mk

PKG_NAME:=musl-getent
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/musl-getent
  SECTION:=devel
  CATEGORY:=Development
  TITLE:=musl-getent
  DEPENDS:=
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) $(TARGET_CONFIGURE_OPTS)
endef

define Package/musl-getent/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/musl-getent $(1)/usr/bin/getent
endef

$(eval $(call BuildPackage,musl-getent))

