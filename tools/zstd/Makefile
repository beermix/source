include $(TOPDIR)/rules.mk

PKG_NAME:=zstd
PKG_VERSION:=1.4.5

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/facebook/zstd/releases/download/v$(PKG_VERSION)
PKG_HASH:=98e91c7c6bf162bf90e4e70fdbc41a8188b9fa8de5ad840c401198014406ce9e

PKG_LICENSE:=BSD-3-Clause
PKG_LICENSE_FILES:=LICENSE
PKG_CPE_ID:=cpe:/a:facebook:zstandard

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

HOST_MAKE_FLAGS = PREFIX=$(HOST_BUILD_PREFIX) HAVE_ZLIB=0 HAVE_LZMA=0 HAVE_LZ4=0

$(eval $(call HostBuild))
