#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=expat
PKG_CPE_ID:=cpe:/a:libexpat:expat
PKG_VERSION:=2.2.9

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_HASH:=f1063084dc4302a427dabcca499c8312b3a32a29b7d2506653ecc8f950a9a237
PKG_SOURCE_URL:=https://github.com/libexpat/libexpat/releases/download/R_2_2_9

PKG_INSTALL:=1

include $(INCLUDE_DIR)/host-build.mk
include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libexpat
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=An XML parsing library
  URL:=https://libexpat.github.io/
endef

define Package/libexpat/description
 A fast, non-validating, stream-oriented XML parsing library.
endef

# TARGET_CFLAGS += $(FPIC)

CMAKE_OPTIONS += \
	-DEXPAT_BUILD_DOCS=0 \
	-DEXPAT_BUILD_TOOLS=0 \
	-DEXPAT_BUILD_EXAMPLES=0 \
	-DEXPAT_BUILD_TESTS=0 \

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/expat{,_external}.h $(1)/usr/include/

	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/*.pc $(1)/usr/lib/pkgconfig/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libexpat.so* $(1)/usr/lib/
endef

define Package/libexpat/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libexpat.so.* $(1)/usr/lib/
endef

$(eval $(call HostBuild))
$(eval $(call BuildPackage,libexpat))
