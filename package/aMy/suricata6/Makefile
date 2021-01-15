#
# Copyright (C) 2006-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=suricata
PKG_VERSION:=6.0.1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_DATE:=2020-12-04
PKG_SOURCE_VERSION:=e860b9eee96cb112a45151237d4b23fd0a9efb22
PKG_SOURCE_URL:=https://github.com/OISF/suricata.git
PKG_HASH:=skip

SURICATA-UPDATE_SOURCE_DATE:=2020-10-05
SURICATA-UPDATE_SOURCE_VERSION:=86e530cbbfc78ac327072750a12edf888e6b8cae
SURICATA-UPDATE_SOURCE_URL:=https://github.com/OISF/suricata-update.git
SURICATA-UPDATE_HASH:=skip

PKG_FIXUP:=autoreconf
PKG_FIXUP:=patch-libtool

PKG_INSTALL:=1
HOST_BUILD_DEPENDS:=rust/host python3/host luajit/host

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk
include ../rust/rustc-triple.mk

define Package/suricata6
    SUBMENU:=Firewall
    SECTION:=net
    CATEGORY:=Network
    DEPENDS:=+jansson +libcap-ng +libevent2 +libhiredis +liblz4 \
      +libmagic +libpcap +libpcre +libmaxminddb +libnet-1.2.x \
	 +libnetfilter-log +libnetfilter-queue +libnfnetlink +libnss \
	 +libopenssl +luajit +python3 +python3-pip +python3-yaml \
	 +python3-yaml-src +zlib $(ICONV_DEPENDS)
    TITLE:=OISF Suricata IDS
    URL:=https://www.openinfosecfoundation.org/
endef

CONFIGURE_VARS += \
	CARGO_HOME=$(CARGO_HOME) \
	ac_cv_path_CARGO="$(CARGO_HOME)/bin/cargo" \
	ac_cv_path_RUSTC="$(CARGO_HOME)/bin/rustc"
#	RUSTFLAGS="-C linker=$(TARGET_CC_NOCACHE) -C ar=$(TARGET_AR)"

CONFIGURE_ARGS = \
  	--prefix="/usr" \
  	--sysconfdir="/etc" \
  	--localstatedir="/var" \
  	--enable-nfqueue \
     --enable-af-packet \
     --enable-unittests \
	--enable-luajit \
	--enable-geoip \
     --enable-debug \
	--enable-hiredis \
     --enable-profiling \
     --enable-profiling-locks \
	--host=$(RUSTC_TARGET_ARCH) \
	--build=$(RUSTC_HOST_ARCH) \
	--with-suricata-update

define Build/InstallDev
	$(call HostPython3/Run,,$(HOST_PYTHON3_PIP_INSTALL_HOST) PyYAML)
endef

define Build/Prepare
	$(call Build/Prepare/Default)
	cd $(PKG_BUILD_DIR) && git clone https://github.com/OISF/libhtp.git
	$(CONFIGURE_VARS) cargo install cbindgen
endef

define Build/Configure
	cd $(PKG_BUILD_DIR) && $(CONFIGURE_VARS) ./autogen.sh
	$(call Build/Configure/Default)
endef

define Package/suricata6/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/suricata $(1)/usr/bin/suricata
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/suricatactl $(1)/usr/bin/suricatactl
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/suricatasc $(1)/usr/bin/suricatasc

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) -r $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib/

	$(INSTALL_DIR) $(1)/usr/include
	$(CP) -r $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/

	$(INSTALL_DIR) $(1)/usr/share
	$(CP) -r $(PKG_INSTALL_DIR)/usr/share/* $(1)/usr/share/

	$(INSTALL_DIR) $(1)/etc/suricata
	$(CP) $(PKG_BUILD_DIR)/suricata.yaml \
	$(PKG_BUILD_DIR)/etc/classification.config \
	$(PKG_BUILD_DIR)/threshold.config \
	$(PKG_BUILD_DIR)/etc/reference.config \
	$(1)/etc/suricata/

#	$(INSTALL_DIR) $(1)/etc/suricata/rules
#	$(CP) $(PKG_BUILD_DIR)/rules/*.rules $(1)/etc/suricata/rules/
#	$(INSTALL_DIR) $(1)/etc/init.d
#	$(INSTALL_BIN) ./files/suricata.init $(1)/etc/init.d/suricata
endef

$(eval $(call BuildPackage,suricata6))
