#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ytop
PKG_SOURCE_VERSION:=0.6.2
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/cjbassi/ytop
PKG_HASH:=skip

include $(INCLUDE_DIR)/package.mk
include ../rust/rustc-triple.mk

define Package/ytop
  SECTION:=admin
  CATEGORY:=Administration
  TITLE:=System and process monitor for Linux
endef

CONFIGURE_VARS += \
	CARGO_HOME=$(CARGO_HOME) \
	ac_cv_path_CARGO="$(CARGO_HOME)/bin/cargo" \
	ac_cv_path_RUSTC="$(CARGO_HOME)/bin/rustc"
#	RUSTFLAGS="-C linker=$(TARGET_CC_NOCACHE) -C ar=$(TARGET_AR)"

define Build/Compile
	cd $(PKG_BUILD_DIR)
	$(CONFIGURE_VARS) cargo build
endef

#define Build/Compile
#        cd $(PKG_BUILD_DIR)
#        cargo build --release
#endef

define Package/ytop/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ytop $(1)/usr/bin/
endef

$(eval $(call BuildPackage,ytop))
