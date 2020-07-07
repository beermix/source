#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=telegramopenwrt
PKG_VERSION:=2a99a68

PKG_SOURCE_PROTO:=git
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_URL:=https://github.com/alexwbaule/telegramopenwrt.git
PKG_SOURCE_VERSION:=$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/telegramopenwrt
  SECTION:=admin
  CATEGORY:=Administration
  TITLE:=telegramopenwrt
  URL:=https://github.com/alexwbaule/telegramopenwrt
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/telegramopenwrt/install
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_DIR) $(1)/sbin
	$(INSTALL_DIR) $(1)/usr/lib/telegramopenwrt/plugins
	$(INSTALL_DIR) $(1)/usr/lib/telegramopenwrt/plugins/actions
	$(INSTALL_DIR) $(1)/usr/lib/telegramopenwrt/plugins/ctx
	$(INSTALL_DIR) $(1)/usr/lib/telegramopenwrt/plugins/help
endef

$(eval $(call BuildPackage,telegramopenwrt))
