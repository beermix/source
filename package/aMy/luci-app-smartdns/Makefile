# 
# Copyright 2018-2020 Nick Peng <pymumu@gmail.com>
# Licensed to the public under the GPL V3 License.

include $(TOPDIR)/rules.mk

PKG_NAME:=luci-app-smartdns
PKG_LICENSE:=GPL-3.0-or-later
PKG_MAINTAINER:=Nick Peng <pymumu@gmail.com>
PKG_VERSION:=1.3.0

include $(INCLUDE_DIR)/package.mk

define Package/luci-app-smartdns
  SECTION:=smartdns
  CATEGORY:=LuCI
  SUBMENU:=2. Smartdns
  TITLE:=luci For smartdns
  DEPENDS:=+libpthread +libopenssl +smartdns
  PKGARCH:=all
  URL:=https://github.com/frainzy1477/smartdns/
endef

define Package/luci-app-smartdns/description
	Luci Interface for smartdns.
endef

define Build/Prepare
	po2lmo ${CURDIR}/po/zh-cn/smartdns.po ${CURDIR}/po/zh-cn/smartdns.zh-cn.lmo
endef

define Build/Configure
endef

define Build/Compile
endef


define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/www/luci-static/resources/view/smartdns
	$(INSTALL_DIR) $(1)/usr/lib/lua/luci/i18n
	$(INSTALL_DIR) $(1)/usr/share/
	$(INSTALL_DIR) $(1)/usr/share/luci
	$(INSTALL_DIR) $(1)/usr/share/luci/menu.d
	$(INSTALL_DIR) $(1)/usr/share/rpcd	
	$(INSTALL_DIR) $(1)/usr/share/rpcd/acl.d

	$(INSTALL_DATA) ./po/zh-cn/smartdns.zh-cn.lmo $(1)/usr/lib/lua/luci/i18n/
	$(INSTALL_BIN) ./root/usr/share/rpcd/acl.d/luci-app-smartdns.json $(1)/usr/share/rpcd/acl.d/
	$(INSTALL_BIN) ./root/usr/share/luci/menu.d/luci-app-smartdns.json $(1)/usr/share/luci/menu.d/
	$(INSTALL_BIN) ./htdocs/luci-static/resources/view/smartdns/smartdns.js $(1)/www/luci-static/resources/view/smartdns/


endef
$(eval $(call BuildPackage,$(PKG_NAME)))


# call BuildPackage - OpenWrt buildroot signature
