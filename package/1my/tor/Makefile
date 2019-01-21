#
# Copyright (C) 2008-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
# https://dist.torproject.org/?C=M;O=D | https://github.com/torproject/tor/branches/active

include $(TOPDIR)/rules.mk

PKG_NAME:=tor
PKG_VERSION:=4484481

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/torproject/tor.git
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

PKG_INSTALL:=1
PKG_FIXUP:=autoreconf

include $(INCLUDE_DIR)/package.mk

define Package/tor/Default
  SECTION:=net
  CATEGORY:=Network
  URL:=https://www.torproject.org/
  USERID:=tor=52:tor=52
endef

define Package/tor/Default/description
 Tor is a toolset for a wide range of organizations and people that want to
 improve their safety and security on the Internet. Using Tor can help you
 anonymize web browsing and publishing, instant messaging, IRC, SSH, and
 more. Tor also provides a platform on which software developers can build
 new applications with built-in anonymity, safety, and privacy features.
endef

define Package/tor
$(call Package/tor/Default)
  TITLE:=An anonymous Internet communication system
  #DEPENDS:=+libevent2 +libopenssl +libpthread +librt +zlib +libcap +libatomic +liblzma +zstd
  DEPENDS:=+libevent2 +libopenssl +libpthread +librt +zlib +libcap +libatomic
endef

define Package/tor/description
$(call Package/tor/Default/description)
 This package contains the tor daemon.
endef

define Package/tor-gencert
$(call Package/tor/Default)
  TITLE:=Tor certificate generation
  DEPENDS:=+tor
endef

define Package/tor-gencert/description
$(call Package/tor/Default/description)
 Generate certs and keys for Tor directory authorities
endef

define Package/tor-resolve
$(call Package/tor/Default)
  TITLE:=tor hostname resolve
  DEPENDS:=+tor
endef

define Package/tor-resolve/description
$(call Package/tor/Default/description)
 Resolve a hostname to an IP address via tor 
endef

define Package/tor-geoip
$(call Package/tor/Default)
  TITLE:=GeoIP db for tor
  DEPENDS:=+tor
endef

define Package/tor-geoip/description
$(call Package/tor/Default/description)
 This package contains a GeoIP database mapping IP addresses to countries.
endef

define Package/tor/conffiles
/etc/tor/torrc
/var/lib/tor/fingerprint
/var/lib/tor/keys/*
endef

CONFIGURE_ARGS += \
	--with-libevent-dir="$(STAGING_DIR)/usr" \
	--with-ssl-dir="$(STAGING_DIR)/usr" \
	--with-openssl-dir="$(STAGING_DIR)/usr" \
	--with-zlib-dir="$(STAGING_DIR)/usr" \
	--enable-silent-rules \
	--disable-asciidoc \
	--disable-seccomp \
	--disable-libscrypt \
	--disable-unittests \
	--enable-zstd=no \
	--enable-lzma=no \
	--with-tor-user=tor \
	--with-tor-group=tor \
	--disable-android \
	--disable-libfuzzer \
	--disable-module-dirauth \
	--enable-pic \
	--disable-rust \
	--disable-restart-debugging \
	--disable-zstd-advanced-apis

EXTRA_CFLAGS += -std=gnu99

TARGET_CFLAGS := $(filter-out -O%,$(TARGET_CFLAGS)) -O2 -funroll-loops -fasynchronous-unwind-tables
TARGET_CXXFLAGS := $(filter-out -O%,$(TARGET_CXXFLAGS)) -O2 -funroll-loops -fasynchronous-unwind-tables
EXTRA_LDFLAGS += -latomic

ifneq ($(CONFIG_SSP_SUPPORT),y)
	CONFIGURE_ARGS += \
		--disable-gcc-hardening
else
	EXTRA_CFLAGS += -fPIC
endif

CONFIGURE_VARS += \
	CROSS_COMPILE="yes"

define Package/tor/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/tor $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/torify $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/tor.init $(1)/etc/init.d/tor
	$(INSTALL_DIR) $(1)/etc/tor
	$(INSTALL_CONF) $(PKG_INSTALL_DIR)/etc/tor/torrc.sample $(1)/etc/tor/torrc
endef

define Package/tor-gencert/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/tor-gencert $(1)/usr/sbin/
endef

define Package/tor-resolve/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/tor-resolve $(1)/usr/sbin/
endef

define Package/tor-geoip/install
	$(INSTALL_DIR) $(1)/usr/share/tor
	$(CP) $(PKG_INSTALL_DIR)/usr/share/tor/geoip $(1)/usr/share/tor/
	$(CP) $(PKG_INSTALL_DIR)/usr/share/tor/geoip6 $(1)/usr/share/tor/
endef

$(eval $(call BuildPackage,tor))
$(eval $(call BuildPackage,tor-gencert))
$(eval $(call BuildPackage,tor-resolve))
$(eval $(call BuildPackage,tor-geoip))
