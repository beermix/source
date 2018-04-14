#

include $(TOPDIR)/rules.mk

PKG_NAME:=autoconf-archive
PKG_VERSION:=2018.03.13

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=@GNU/autoconf-archive
PKG_HASH:=6175f90d9fa64c4d939bdbb3e8511ae0ee2134863a2c7bf8d9733819efa6e159

PKG_BUILD_DEPENDS:=autoconf-archive/host gettext

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/host-build.mk

HOST_FIXUP:=autoreconf
PKG_FIXUP:=autoreconf

define Package/autoconf-archive
	SECTION:=devel
	CATEGORY:=Development
	TITLE:=autoconf-archive
endef

$(eval $(call HostBuild))
$(eval $(call BuildPackage,autoconf-archive))