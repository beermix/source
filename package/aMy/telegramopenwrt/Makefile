#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=telegramopenwrt
PKG_VERSION:=4b6d750

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/tarasifua/telegramopenwrt.git
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz

include $(INCLUDE_DIR)/package.mk

define Package/telegramopenwrt
  SECTION:=admin
  CATEGORY:=Administration
  TITLE:=telegramopenwrt
  URL:=https://github.com/alexwbaule/telegramopenwrt
endef

define Build/Compile
	true
endef

define Build/Configure
	true
endef

define Package/telegramopenwrt/install
	#$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_DIR) $(1)/sbin
	$(INSTALL_DIR) $(1)/usr

	$(CP) $(PKG_BUILD_DIR)/etc/init.d $(1)/etc/
	$(CP) $(PKG_BUILD_DIR)/sbin $(1)/
	$(CP) $(PKG_BUILD_DIR)/usr $(1)/
	$(CP) $(PKG_BUILD_DIR)/sbin $(1)/
endef

$(eval $(call BuildPackage,telegramopenwrt))
