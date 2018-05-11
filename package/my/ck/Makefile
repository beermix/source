include $(TOPDIR)/rules.mk

PKG_NAME:=ck
PKG_VERSION:=9587bbb

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/concurrencykit/ck
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

PKG_FIXUP:=autoreconf
include $(INCLUDE_DIR)/package.mk

PKG_INSTALL:=1

define Package/ck
	SECTION:=libs
	CATEGORY:=Libraries
	TITLE:=Zstandard is a real-time compression algorithm
	DEPENDS:=+libpthread
endef

define Build/Configure
	(cd $(PKG_BUILD_DIR); \
		$(TARGET_CONFIGURE_OPTS) \
		./configure \
		--prefix=/usr \
	);
endef


define Package/ck/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libck.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,ck))