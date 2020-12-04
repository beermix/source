# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=rust
#PKG_VERSION:=1.49.0
#PKG_RELEASE:=1
#PKG_LICENSE:=Apache-2.0 MIT
#PKG_LICENSE_FILES:=LICENSE-APACHE LICENSE-MIT

#PKG_SOURCE_PROTO:=git
#PKG_SOURCE_URL:=https://github.com/rust-lang/rust.git
#PKG_SOURCE_DATE:=2020-12-04
#PKG_SOURCE_VERSION:=2218520b8adf8b8e64b817537d9eb0a84840e2f1
#PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.xz


PKG_VERSION:=1.48.0
PKG_SOURCE_SUBDIR:=$(PKG_NAME)c-$(PKG_VERSION)-src
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=https://static.rust-lang.org/dist
PKG_BUILD_DIR:=$(PKG_NAME)c-$(PKG_VERSION)-src

#PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
#PKG_SOURCE_VERSION:=d94c245ea47859cda5b4b7373308589206b97bdc
#PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz
#PKG_MAINTAINER:=semigodking <semigodking@gmail.com>
#PKG_BUIL#_DIR:=$(BUILD_DIR)/$(PKG_NAME)/$(BUILD_VARIANT)/$(PKG_NAME)-$(PKG_VERSION)

PKG_HASH:=skip
PKG_HOST_ONLY:=1

include $(INCLUDE_DIR)/cmake.mk
include $(INCLUDE_DIR)/host-build.mk
include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/download.mk
include ./rustc-triple.mk

HOST_BUILD_DEPENDS:=rust/host ninja/host python3/host
CMAKE_INSTALL:=1

#gen_sha256sum=$(shell mkhash sha256 $(DL_DIR)/$(1))
#fixup_rust_hash=$(shell $(SCRIPT_DIR)/fixup-makefile.pl $(1) fix-hash $(2) $(3))

# Basic Configuration Args that are used across all builds.
# Other build arguments are found in ./rustc-config.mk
#
# Default CONFIGURE_ARGS introduces unknown options - Use this instead
CONFIGURE_ARGS = \
  --host=$(RUSTC_HOST_ARCH) \
  --build=$(RUSTC_HOST_ARCH) \
  --target=$(RUSTC_TARGET_ARCH) \
  --prefix=$(CARGO_HOME) \
  --bindir=$(CARGO_HOME)/bin \
  --libdir=$(CARGO_HOME)/lib \
  --sysconfdir=$(CARGO_HOME)/etc \
  --datadir=$(CARGO_HOME)/share \
  --mandir=$(CARGO_HOME)/man \
  --infodir=$(CARGO_HOME)/info \
  --localstatedir=/var \
  --release-channel=nightly \
  --enable-lld \
  --enable-extended \
  --tools="analysis,cargo,src" \
  --enable-locked-deps \
  --set=target.$(RUSTC_TARGET_ARCH).linker=$(TARGET_CC_NOCACHE) \
  --set=target.$(RUSTC_TARGET_ARCH).cc=$(TARGET_CC_NOCACHE) \
  --set=target.$(RUSTC_TARGET_ARCH).cxx=$(TARGET_CXX_NOCACHE) \
  --set=target.$(RUSTC_TARGET_ARCH).ar=$(TARGET_AR) \
  --set=target.$(RUSTC_TARGET_ARCH).ranlib=$(TARGET_RANLIB)

# Because we override CONFIGURE_ARGS, this needs to go here.
include ./rustc-config.mk

RUST_TMP_DIR:=$(TMP_DIR)/rust-install
RUST_INSTALL_FILE_NAME:=$(PKG_NAME)-$(PKG_VERSION)-$(RUSTC_HOST_ARCH)_$(RUSTC_TARGET_ARCH)-install.tar.xz
RUST_INSTALL_FILE_VERIFY:=$(call check_hash,$(RUST_INSTALL_FILE_NAME),$(RUST_INSTALL_FILE_HASH),RUST_INSTALL_FILE_HASH)
RUST_INSTALL_UNINSTALL:=$(CARGO_HOME)/lib/rustlib/uninstall.sh
RUST_INSTALL_BINARIES:=$(CURDIR)/install_binaries.sh $(RUST_TMP_DIR) $(RUST_INSTALL_FILE_NAME) $(CARGO_HOME)
RUST_INSTALL_FILE_HASH:=skip

RUST_BINARY=$(or $(and $(wildcard $(DL_DIR)/$(RUST_INSTALL_FILE_NAME)),true),false)

define Host/Clean
	$(info In Clean)
	$(call Host/Clean/Default)

	[ -f $(RUST_INSTALL_UNINSTALL) ] && \
	    $(RUST_INSTALL_UNINSTALL) || echo No Uninstall Found

	rm -rf $(BUILD_DIR_HOST)/rust
endef

define Host/Configure
	$(info In Configure)
	# Required because OpenWrt Default CONFIGURE_ARGS contain extra
	# args that cause errors
	[ $(RUST_BINARY) = true ] && \
	( true ) || \
	  ( cd $(HOST_BUILD_DIR) && \
	     RUST_BACKTRACE=full \
		./configure $(CONFIGURE_ARGS) )
endef

define Host/Compile
	$(info In Compile)
	[ $(RUST_BINARY) = true ] && ( true ) || \
	  ( cd $(HOST_BUILD_DIR) && \
	     ( RUST_BACKTRACE=full \
		$(PYTHON) x.py --config ./config.toml dist cargo extended \
		   library/std llvm-tools miri rust-dev rustc-dev src \
		   src/librustc src/lldb_batchmode.py src/tools/build-manifest ) && \
		   ( $(RUST_INSTALL_BINARIES)))
endef

define Host/CreateBinaries
	# This creates the installation binary in downloads
	cd $(HOST_BUILD_DIR)/build/dist && \
	   $(RM) *.gz && \
	   $(call dl_tar_pack,$(DL_DIR)/$(RUST_INSTALL_FILE_NAME),.)

	$(call fixup_rust_hash, $(CURDIR)/Makefile, \
	   RUST_INSTALL_FILE_HASH, \
	   $(call gen_sha256sum,$(RUST_INSTALL_FILE_NAME)))
endef


define Host/Install
	cd $(RUST_TMP_DIR) && \
	   $(TAR) -xJf $(DL_DIR)/$(RUST_INSTALL_FILE_NAME) && \
	   find -iname "*.xz" -exec $(TAR) -x -J -f {} ";" && \
	   find ./* -type f -name install.sh -execdir sh {} --prefix=$(CARGO_HOME) --disable-ldconfig \;
	$(RM) -rf $(RUST_TMP_DIR)
endef

define Host/Prepare
	# Allows outside packages to call $$(BUILD_DIR_HOST)/rust as the dir
	# rather than needing the version number.
	[ -L $(BUILD_DIR_HOST)/rust ] || \
	   (cd $(BUILD_DIR_HOST); ln -s "$(PKG_NAME)-$(PKG_VERSION)" rust)

	[ -d $(RUST_TMP_DIR) ] || \
	   mkdir -p $(RUST_TMP_DIR)

	$(call Host/Prepare/Default)
endef

define Package/rust
  SECTION:=lang
  CATEGORY:=Languages
  TITLE:=Rust Programming Language Compiler
  URL:=https://www.rust-lang.org/
  #DEPENDS:=+python3 +ninja +pkg-config +libopenssl +libyaml \
    +libyaml-cpp +libunwind +openssl-util +python3-yaml
endef

define Package/rust/description
  Rust lang
endef

define Package/rust/config
	source "$(SOURCE)/Config.in"
endef

$(eval $(call HostBuild))
$(eval $(call BuildPackage,rust))
