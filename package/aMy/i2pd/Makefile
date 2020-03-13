#
# Copyright (C) 2015, 2016 gxcreator
# Copyright (C) 2017 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
# https://github.com/PurpleI2P/i2pd

include $(TOPDIR)/rules.mk

PKG_NAME:=i2pd
PKG_VERSION:=dd8200e

PKG_SOURCE_PROTO:=git
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_URL:=https://github.com/PurpleI2P/i2pd.git
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_LICENSE:=BSD-3-clause

PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

export CMAKE_SOURCE_DIR=$(PKG_INSTALL_DIR)/../build

CMAKE_OPTIONS += \
	-DWITH_AESNI=0 \
	-DWITH_AVX=0 \
	-DWITH_HARDENING=0 \
	-DWITH_LIBRARY=0 \
	-DCMAKE_BUILD_TYPE=Release \
	-DBoost_USE_STATIC_LIBS=1 \
	-DBoost_USE_STATIC_RUNTIME=0 \
	-DWITH_UPNP=0

define Package/i2pd
	SECTION:=net
	CATEGORY:=Network
	DEPENDS:=+libstdcpp +libpthread +librt +libopenssl +boost +boost-system +boost-filesystem \
	         +boost-program_options +boost-date_time +libatomic +zlib
	TITLE:=full-featured C++ implementation of I2P client
	URL:=https://github.com/PurpleI2P/i2pd
	USERID:=i2pd:i2pd
endef

define Package/i2pd/description
	I2P (Invisible Internet Protocol) is a universal anonymous network layer. All
	communications over I2P are anonymous and end-to-end encrypted, participants
	don't reveal their real IP addresses.
endef

define Package/i2pd/conffiles
	/etc/config/i2pd
	/etc/i2pd/i2pd.conf
	/etc/i2pd/tunnels.conf
	/etc/i2pd/tunnels.d/*
endef

# TARGET_LDFLAGS+=-latomic

define Package/i2pd/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/i2pd $(1)/usr/sbin
	$(INSTALL_DIR) $(1)/usr/share/i2pd
	$(CP) $(PKG_BUILD_DIR)/contrib/certificates  $(1)/usr/share/i2pd
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./files/i2pd.config $(1)/etc/config/i2pd
	$(INSTALL_DIR) $(1)/etc/i2pd
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/contrib/i2pd.conf $(1)/etc/i2pd
	$(SED) ' \
		s/127.0.0.1/192.168.1.1/g; \
		s/datadir = \/var\/lib/datadir = \/etc/ \
	' $(1)/etc/i2pd/i2pd.conf
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/contrib/tunnels.conf $(1)/etc/i2pd
	$(INSTALL_DIR) $(1)/etc/i2pd/tunnels.d
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/contrib/tunnels.d/*.conf  $(1)/etc/i2pd/tunnels.d
	# subscriptions.txt deprecated, see #8088
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/i2pd.init $(1)/etc/init.d/i2pd
endef

$(eval $(call BuildPackage,i2pd))
