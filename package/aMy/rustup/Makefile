#
# Copyright (C) 2006-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=rustup
PKG_VERSION:=995002f

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/rust-lang/rustup.git
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

include $(INCLUDE_DIR)/host-build.mk
include $(INCLUDE_DIR)/package.mk

define Package/rustup
    SECTION:=lang
    CATEGORY:=Languages
    TITLE:=rustup - Rust Programming Language Installer
    URL:=https://www.rust-lang.org/
endef

define Package/rustup/description
 rustup installs The Rust Programming Language from the official release
 channels, enabling you to easily switch between stable, beta, and nightly
 compilers and keep them updated. It makes cross-compiling simpler with binary
 builds of the standard library for common platforms. And it runs on all
 platforms Rust supports, including Windows.
endef

RUSTC_TARGET_ARCH:= i686-unknown-linux-musl
HOST_RUST_DIR:=$(BUILD_DIR_HOST)/.rustup
HOST_CARGO_DIR:=$(BUILD_DIR_HOST)/.cargo

define Host/Configure
	RUSTUP_HOME=$(HOST_RUST_DIR) \
	CARGO_HOME=$(HOST_CARGO_DIR) \
	$(BUILD_DIR_HOST)/$(PKG_NAME)-$(PKG_VERSION)/rustup-init.sh -y -v --profile default --target $(RUSTC_TARGET_ARCH)
endef

define Host/Install
	RUSTUP_HOME=$(HOST_RUST_DIR) CARGO_HOME=$(HOST_CARGO_DIR) $(HOST_CARGO_DIR)/bin/rustup target add $(RUSTC_TARGET_ARCH)
endef

define Package/rustup/install
	true
endef

$(eval $(call HostBuild))
$(eval $(call BuildPackage,rustup))
