#
# Copyright (C) 2007-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=file
PKG_VERSION:=5.36
PKG_RELEASE:=3

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=https://fossies.org/linux/misc/
PKG_HASH:=

PKG_LICENSE:=BSD-2c
PKG_LICENSE_FILES:=COPYING

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/file/Default
  TITLE:=File type determination
  URL:=ftp://ftp.astron.com/pub/file/
  MAINTAINER:=Marko Ratkaj <marko.ratkaj@sartura.hr>
endef

define Package/file
$(call Package/file/Default)
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE+= utility
  DEPENDS:=+libmagic +libexpat +libattr
endef

define Package/libmagic
$(call Package/file/Default)
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE+= library
  DEPENDS:=+zlib
endef

CONFIGURE_ARGS += \
	--disable-shared \
	--enable-static \
	
TARGET_CFLAGS := $(filter-out -O%,$(TARGET_CFLAGS)) -Os
TARGET_CXXFLAGS := $(filter-out -O%,$(TARGET_CFLAGS)) -Os

MAKE_PATH := src

TARGET_CFLAGS += $(FPIC)

define Build/Compile/magic
	( cd $(PKG_BUILD_DIR)/magic/Magdir; \
		for f in `ls`; do \
			cat $$$${f}; \
		done \
	) > $(PKG_BUILD_DIR)/magic/magic
endef
Hooks/Compile/Post += Build/Compile/magic

define Build/Install/magic
	$(INSTALL_DIR) $(PKG_INSTALL_DIR)/usr/share/file
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/magic/magic $(PKG_INSTALL_DIR)/usr/share/file/
endef
Hooks/Install/Post += Build/Install/magic

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/include/magic.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/libmagic.a $(1)/usr/lib/
endef

define Package/file/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/file $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/usr/share/misc
	$(SED) "/^#/d" $(PKG_INSTALL_DIR)/usr/share/file/magic
	$(SED) "/^$$$$/d" $(PKG_INSTALL_DIR)/usr/share/file/magic
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/share/file/magic $(1)/usr/share/misc/

	# For some reason both "magic" and "magic.mgc" MUST exist
	#ln -sf magic $(1)/usr/share/misc/magic.mgc
endef

define Package/libmagic/install
	$(INSTALL_DIR) $(1)/usr/lib
#	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libmagic.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,file))
$(eval $(call BuildPackage,libmagic))
