include $(TOPDIR)/rules.mk

PKG_NAME:=zstd
PKG_VERSION:=v1.3.4

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/facebook/zstd
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

include $(INCLUDE_DIR)/package.mk

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

define Package/zstd
	SECTION:=libs
	CATEGORY:=Libraries
	TITLE:=Zstandard is a real-time compression algorithm
	URL:=http://facebook.github.io/zstd/
	DEPENDS:=+libpthread
endef

define Build/Compile
	$(MAKE) -C "$(PKG_BUILD_DIR)/lib" $(MAKE_INSTALL_FLAGS) \
	  CC="$(TARGET_CC)" \
	  CFLAGS="$(TARGET_CFLAGS) -O3 -falign-functions=32 -fno-math-errno -fno-semantic-interposition -fno-trapping-math" \
	  PREFIX="$(CONFIGURE_PREFIX)" \
	  PREFIX=/usr \
	  lib-release
endef

define Build/InstallDev
	$(CP) $(PKG_INSTALL_DIR)/* $(1)/
endef

define Package/zstd/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/local/lib/libzstd.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,zstd))


