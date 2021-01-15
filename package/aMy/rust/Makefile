# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=rust
PKG_VERSION:=1.49.0
PKG_RELEASE:=1

PKG_LICENSE:=Apache-2.0 MIT
PKG_LICENSE_FILES:=LICENSE-APACHE LICENSE-MIT

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/rust-lang/rust.git
PKG_SOURCE_DATE:=2020-11-11
PKG_SOURCE_VERSION:=e38fb306b7f5e65cca34df2dab1f0db15e1defb4
PKG_HASH:=skip
PKG_HOST_ONLY:=1

include $(INCLUDE_DIR)/cmake.mk
include $(INCLUDE_DIR)/host-build.mk
include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/download.mk
include ./rustc-triple.mk

HOST_BUILD_DEPENDS:=ninja/host python3/host
PKG_BUILD_DEPENDS:=rust/host
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
  --target=i686-unknown-linux-musl \
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
  --enable-manage-submodules \
  --enable-optimize-llvm \
  --enable-missing-tools \
  --enable-full-tools \
  --enable-ninja \
  --enable-option-checking \
  --set=target.i686-unknown-linux-musl.linker=$(TARGET_CC_NOCACHE) \
  --set=target.i686-unknown-linux-musl.cc=$(TARGET_CC_NOCACHE) \
  --set=target.i686-unknown-linux-musl.cxx=$(TARGET_CXX_NOCACHE) \
  --set=target.i686-unknown-linux-musl.ar=$(TARGET_AR) \
  --set=target.i686-unknown-linux-musl.ranlib=$(TARGET_RANLIB)

# Because we override CONFIGURE_ARGS, this needs to go here.
include ./rustc-config.mk

RUST_TMP_DIR:=$(TMP_DIR)/rust-install
RUST_INSTALL_FILE_NAME:=$(PKG_NAME)-$(PKG_VERSION)-$(RUSTC_HOST_ARCH)_i686-unknown-linux-musl-install.tar.xz
RUST_INSTALL_FILE_VERIFY:=$(call check_hash,$(RUST_INSTALL_FILE_NAME),$(RUST_INSTALL_FILE_HASH),RUST_INSTALL_FILE_HASH)
RUST_INSTALL_UNINSTALL:=$(CARGO_HOME)/lib/rustlib/uninstall.sh
RUST_INSTALL_BINARIES:=$(CURDIR)/install_binaries.sh $(RUST_TMP_DIR) $(DL_DIR)/$(RUST_INSTALL_FILE_NAME) $(CARGO_HOME)
RUST_INSTALL_FILE_HASH:=skip

RUST_BINARY=$(or $(and $(wildcard $(DL_DIR)/$(RUST_INSTALL_FILE_NAME)),true),false)

define Host/Clean
	$(call Host/Clean/Default)

	[ -f $(RUST_INSTALL_UNINSTALL) ] && \
	    $(RUST_INSTALL_UNINSTALL) || echo No Uninstall Found

	rm -rf $(BUILD_DIR_HOST)/rust
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

ifeq ($(RUST_BINARY),true)
include ./rust_install.mk
else
include ./rust_compile.mk
endif

#define Host/InstallDev
#	[ $(RUST_BINARY) = true ] && ( sh $(RUST_INSTALL_BINARIES) )
#endef

define Host/Compile-Bak
	[ $(RUST_BINARY) = true ] && ( true ) || \
	  ( cd $(HOST_BUILD_DIR) && \
	     ( RUST_BACKTRACE=full \
		$(PYTHON) x.py --config ./config.toml dist cargo extended \
		   library/std llvm-tools miri rust-dev rustc-dev src \
		   src/librustc src/lldb_batchmode.py src/tools/build-manifest ))
endef

define Host/CreateBinaries
	cd $(HOST_BUILD_DIR)/build/dist && \
	   $(RM) *.gz && \
	   $(call dl_tar_pack,$(DL_DIR)/$(RUST_INSTALL_FILE_NAME),.)

	$(eval $(call fixup_rust_hash, $(CURDIR)/Makefile, \
	   RUST_INSTALL_FILE_HASH, \
	   $(call gen_sha256sum,$(RUST_INSTALL_FILE_NAME))))
endef

define Package/rust
  SECTION:=lang
  CATEGORY:=Languages
  TITLE:=Rust Programming Language Compiler
  URL:=https://www.rust-lang.org/
  #DEPENDS:=+python3 +ninja +pkg-config +libopenssl +libyaml +libyaml-cpp +openssl-util +python3-yaml
endef

define Package/rust/description
  Rust lang
endef

define Package/rust/config
	source "$(SOURCE)/Config.in"
endef

$(eval $(call HostBuild))
$(eval $(call BuildPackage,rust))
