include $(TOPDIR)/rules.mk

PKG_NAME:=zstd
PKG_VERSION:=v1.3.4

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/facebook/zstd
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

include $(INCLUDE_DIR)/package.mk

define Package/zstd
	SECTION:=libs
	CATEGORY:=Libraries
	TITLE:=Zstandard is a real-time compression algorithm
	URL:=http://facebook.github.io/zstd/
endef

TARGET_CFLAGS += $(FPIC)

define Build/Compile
	$(MAKE) -C "$(PKG_BUILD_DIR)/lib" $(MAKE_INSTALL_FLAGS) \
	  CC="$(TARGET_CC)" \
	  CFLAGS="$(TARGET_CFLAGS)" \
	  PREFIX="$(CONFIGURE_PREFIX)" \
	  install
endef

define Build/InstallDev
	$(CP) $(PKG_INSTALL_DIR)/* $(1)/
endef

define Package/zstd/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libzstd.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,zstd))


