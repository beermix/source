include $(TOPDIR)/rules.mk

PKG_NAME:=exfatprogs
PKG_VERSION:=1.0.2
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/$(PKG_NAME)/$(PKG_NAME)/tar.gz/$(PKG_VERSION)?
PKG_HASH:=e7f14f32dd67601ff42717f432093a400de878774796f6f1684fb9dbf0d499e1

PKG_MAINTAINER:=Daniel Golle <daniel@makrotopia.org>
PKG_LICENSE:=GPL-2.0-only
PKG_LICENSE_FILES:=COPYING

PKG_FIXUP:=autoreconf
PKG_BUILD_PARALLEL:=1
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/exfatprogs/Default
  SECTION:=utils
  CATEGORY:=Utilities
  SUBMENU:=Filesystem
  DEPENDS:=+libexfat
  URL:=https://github.com/exfatprogs/exfatprogs
endef

define Package/exfat-mkfs
  $(Package/exfatprogs/Default)
  TITLE:=Utility for creating an exFAT File System
endef

define Package/exfat-fsck
  $(Package/exfatprogs/Default)
  TITLE:=Utility for checking/repairing an exFAT File System
endef

define Package/libexfat
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Library for exFAT File System tools
  DEPENDS:=+libuuid
  ABI_VERSION:=1
endef

CONFIGURE_ARGS += \
	--enable-shared \
	--disable-static

define Package/libexfat/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libexfat.so.* $(1)/usr/lib/
endef

define Package/exfat-mkfs/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/mkfs.exfat $(1)/usr/sbin
endef

define Package/exfat-fsck/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/fsck.exfat $(1)/usr/sbin
endef

$(eval $(call BuildPackage,libexfat))
$(eval $(call BuildPackage,exfat-mkfs))
$(eval $(call BuildPackage,exfat-fsck))
