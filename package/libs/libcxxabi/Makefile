
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libcxxabi
PKG_VERSION:=9.0.1
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://git.llvm.org/git/libcxxabi
PKG_SOURCE_VERSION:=a88633b46c401e6be38b93cf08660f137f86664d
PKG_MIRROR_HASH:=ec593f7efcb6ffe1b35a690371b0944f80251b9aabc5a9f074b83f5d868f23a4

PKG_MAINTAINER:=Rosen Penev <rosenp@gmail.com>
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE.txt

#PKG_BUILD_DEPENDS:=libcxx/host
PKG_BUILD_PARALLEL:=1
CMAKE_BINARY_SUBDIR:=build

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libcxxabi
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=LLVM libcxxabi
  URL:=https://libcxxabi.llvm.org/
  DEPENDS:=+libatomic +libpthread
endef

define Package/libcxxabi/description
  LLVM C++ ABI library
endef

CMAKE_OPTIONS += \
	-DLIBCXXABI_LIBCXX_INCLUDES="$(TOOLCHAIN_DIR)/$(REAL_GNU_TARGET_NAME)/include"
#	-DLIBCXXABI_LIBCXX_INCLUDES="$(STAGING_DIR_HOST)/include/c++/v1"

TARGET_CXXFLAGS += -flto
TARGET_LDFLAGS += -Wl,--gc-sections,--as-needed

define Package/libcxxabi/install
	$(INSTALL_DIR)					$(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libc++.so.*	$(1)/usr/lib/
endef

$(eval $(call BuildPackage,libcxxabi))
