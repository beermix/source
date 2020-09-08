#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=nuttcp
PKG_VERSION:=8.2.2

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://nuttcp.net/nuttcp
PKG_HASH:=7ead7a89e7aaa059d20e34042c58a198c2981cad729550d1388ddfc9036d3983

include $(INCLUDE_DIR)/package.mk

define Package/nuttcp
	SECTION:=net
	CATEGORY:=Network
	TITLE:=nuttcp
endef

TARGET_CFLAGS := -O3 $(filter-out -O%,$(TARGET_CFLAGS))

define Package/nuttcp/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/nuttcp-$(PKG_VERSION) $(1)/usr/bin/nuttcp
endef

$(eval $(call BuildPackage,nuttcp))
