include $(TOPDIR)/rules.mk

PKG_NAME:=zstd
PKG_VERSION:=v1.3.5

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/facebook/zstd
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

export CMAKE_SOURCE_DIR=$(PKG_INSTALL_DIR)/../build/cmake

CMAKE_OPTIONS += \
	-DCMAKE_BUILD_TYPE=Release \
	-DZSTD_BUILD_PROGRAMS=0 \
	-DZSTD_BUILD_SHARED=1 \
	-DZSTD_BUILD_STATIC=0 \
	-DZSTD_BUILD_TESTS=0 \
	-DZSTD_LZMA_SUPPORT=0 \
	-DZSTD_MULTITHREAD_SUPPORT=1 \
	-DZSTD_ZLIB_SUPPORT=0 \

define Package/zstd
	SECTION:=libs
	CATEGORY:=Libraries
	TITLE:=Zstandard is a real-time compression algorithm
	URL:=http://facebook.github.io/zstd/
	DEPENDS:=+libpthread
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/

	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/*.pc $(1)/usr/lib/pkgconfig/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/*.so* $(1)/usr/lib/
endef

define Package/zstd/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/*.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,zstd))