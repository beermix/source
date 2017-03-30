include $(TOPDIR)/rules.mk

PKG_NAME:=uinit
PKG_RELEASE:=1

CMAKE_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/uinit
  SECTION:=base
  CATEGORY:=Base system
  TITLE:=uinit for initramfs
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/uinit/install
	$(INSTALL_DIR) $(TARGET_ROOTFS_DIR)/initramfs
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/init $(TARGET_ROOTFS_DIR)/initramfs/
endef

$(eval $(call BuildPackage,uinit))
