# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#  PKG_VERSION:=73fc3e7
#

include $(TOPDIR)/rules.mk

PKG_NAME:=gettext-tiny
PKG_VERSION:=73fc3e7ef7e016a3874b632fd0475969d288f309

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/sabotage-linux/gettext-tiny.git
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

include $(INCLUDE_DIR)/host-build.mk

define Host/Compile
	$(MAKE) -C $(HOST_BUILD_DIR) \
		prefix=$(STAGING_DIR_HOST) \
		CFLAGS="$(HOST_CFLAGS)" \
		LDFLAGS="$(HOST_LDFLAGS) -fPIC" \
		LIBINTL=NONE

#	cp $(HOST_BUILD_DIR)/extra/gettextize.in $(HOST_BUILD_DIR)/gettextize

#	$(SED) 's,@PACKAGE@,gettext-tools,g;' $(HOST_BUILD_DIR)/gettextize
#	$(SED) 's,@VERSION@,$(GETTEXT_GNU_VERSION),g;' $(HOST_BUILD_DIR)/gettextize
#	$(SED) 's,@ARCHIVE_VERSION@,$(PKG_VERSION),' $(HOST_BUILD_DIR)/gettextize
#	$(SED) 's,@prefix@,$(HOST_BUILD_DIR),g;' $(HOST_BUILD_DIR)/gettextize
#	$(SED) 's,@datarootdir@,$${prefix}/share,g;' $(HOST_BUILD_DIR)/gettextize
#	$(SED) 's,@datadir@,$${prefix}/share,g;' $(HOST_BUILD_DIR)/gettextize
#	$(SED) 's,@PATH_SEPARATOR@,:,g;' $(HOST_BUILD_DIR)/gettextize
#	$(SED) 's,@RELOCATABLE@,no,g;' $(HOST_BUILD_DIR)/gettextize
#	$(SED) 's,@exec_prefix@,$${prefix},g;' $(HOST_BUILD_DIR)/gettextize
#	$(SED) 's,@bindir@,$${exec_prefix}/bin,g;' $(HOST_BUILD_DIR)/gettextize
endef

define Host/Install
	$(MAKE) -C $(HOST_BUILD_DIR) \
		prefix=$(STAGING_DIR_HOST) \
		LIBINTL=NONE install
endef

$(eval $(call HostBuild))
