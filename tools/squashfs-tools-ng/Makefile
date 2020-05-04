include $(TOPDIR)/rules.mk

PKG_NAME:=squashfs-tools-ng
PKG_VERSION:=v0.9.1
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/AgentD/squashfs-tools-ng
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

PKG_FIXUP:=autoreconf

include $(INCLUDE_DIR)/host-build.mk

define Host/Install
	$(INSTALL_DIR) $(STAGING_DIR_HOST)/bin/
	$(INSTALL_BIN) $(HOST_BUILD_DIR)/.libs/gensquashfs $(STAGING_DIR_HOST)/bin/gensquashfs
	$(INSTALL_BIN) $(HOST_BUILD_DIR)/.libs/tar2sqfs $(STAGING_DIR_HOST)/bin/tar2sqfs
	$(INSTALL_BIN) $(HOST_BUILD_DIR)/.libs/libsquashfs* $(STAGING_DIR_HOST)/lib/
endef

define Host/Clean
endef

$(eval $(call HostBuild))
