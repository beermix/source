#
include $(TOPDIR)/rules.mk

PKG_NAME:=tinymembench
PKG_SOURCE_VERSION:=a2cf6d7

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/sun409/tinymembench-pthread

PKG_BUILD_PARALLEL:=0

include $(INCLUDE_DIR)/package.mk

define Package/tinymembench
	SECTION:=net
	CATEGORY:=Network
	TITLE:=tinymembench
endef

TARGET_LDFLAGS+=-lpthread

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) CC="$(TARGET_CC)" CFLAGS="$(TARGET_CFLAGS)" tinymembench
endef

define Package/tinymembench/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/tinymembench $(1)/usr/sbin/tinymembench
endef

$(eval $(call BuildPackage,tinymembench))