#
# Copyright (C) 2006-2011 Openwrt.org
# Copyright (C) 2011 SMBPhone Inc.
# Copyright (C) 2019 Jeffery To
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=slang
PKG_SOURCE_VERSION:=b567e09

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=git://git.jedsoft.org/git/slang.git

PKG_BUILD_PARALLEL:=0

include $(INCLUDE_DIR)/package.mk

define Package/libslang2/Default
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=S-Lang Programmer's Library
  URL:=https://www.jedsoft.org/slang/
endef

define Package/libslang2/Default/description
  Multi-platform programmer's library providing facilities for interactive
  applications.  Includes such things as display/screen management,
  keyboard input, keymaps, etc.  Includes the embeddable S-Lang interpreter.
endef

define Package/libslang2
$(call Package/libslang2/Default)
  DEPENDS:=+terminfo +libreadline +zlib
endef

define Package/libslang2/description
$(call Package/libslang2/Default/description)
endef

TARGET_CFLAGS+= $(FPIC)
# TARGET_CFLAGS:=-Os $(filter-out -O%,$(call qstrip,$(TARGET_CFLAGS)))

CONFIGURE_ARGS+= \
	--disable-warnings \
	--with-terminfo=default \
	--with-readline\
	--without-iconv \
	--without-onig \
	--without-pcre \
	--without-png \
	--with-z \
	--without-x

define Build/Compile
#	$(call Build/Compile/Default,)
	$(call Build/Compile/Default,static)
endef

# Default install last, so that the dynamic slsh is installed
define Build/Install
	$(call Build/Install/Default,install-static)
#	$(call Build/Install/Default,)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/*.h $(1)/usr/include/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libslang.a $(1)/usr/lib/

	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/slang.pc $(1)/usr/lib/pkgconfig/
endef

define Package/libslang2/install
	$(INSTALL_DIR) $(1)/usr/lib
#	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libslang.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libslang2))
