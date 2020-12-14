# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
# https://github.com/rust-lang/rust/tree/beta
include $(TOPDIR)/rules.mk

PKG_NAME:=rust
PKG_VERSION:=1.48.0
#PKG_RELEASE:=2

#PKG_SOURCE_PROTO:=git
#PKG_SOURCE_URL:=https://github.com/rust-lang/rust.git
#PKG_SOURCE_DATE:=2020-12-13
#PKG_SOURCE_VERSION:=d149b6579fb118ea75b16cb7a6afa62695d88992

PKG_SOURCE:=rustc-$(PKG_VERSION)-src.tar.xz
PKG_SOURCE_URL:=https://static.rust-lang.org/dist
PKG_BUILD_DIR:=$(BUILD_DIR)/rustc-$(PKG_VERSION)-src
HOST_BUILD_DIR:=$(BUILD_DIR_HOST)/rustc-$(PKG_VERSION)-src

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

#   --set="target.$(RUSTC_TARGET_ARCH).crt-static=false" --set="target.$(RUSTC_HOST_ARCH).crt-static=false" \
# Basic Configuration Args that are used across all builds.
# Other build arguments are found in ./rustc-config.mk
#   --enable-llvm-link-shared \  --llvm-root=/usr/lib/llvm-7 \
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
  --release-channel=stable \
  --enable-lld \
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
