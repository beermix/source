include $(TOPDIR)/rules.mk

PKG_NAME:=libarchive
PKG_VERSION:=3.4.1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=https://github.com/$(PKG_NAME)/$(PKG_NAME)/releases/download/v$(PKG_VERSION)/ \
		https://www.$(PKG_NAME).org/downloads/
PKG_HASH:=bb84e02f08cc3027e08e2473fc46eb7724ba9244e9c6ef8d122f68addd6042f7

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

HOST_CONFIGURE_ARGS += \
	--disable-shared \
	--enable-static \
	--enable-bsdtar=static \
	--enable-bsdcat=static \
	--disable-bsdcpio \
	--disable-rpath \
	--enable-posix-regex-lib=libc \
	--disable-xattr \
	--disable-acl \
	--without-bz2lib \
	--without-libb2 \
	--without-iconv \
	--without-lz4 \
	--without-zstd \
	--without-cng \
	--without-nettle \
	--without-openssl \
	--without-xml2 \
	--without-expat

define Host/Install
	$(CP) $(HOST_BUILD_DIR)/bsdtar $(STAGING_DIR_HOST)/bin/
	$(CP) $(HOST_BUILD_DIR)/bsdcat $(STAGING_DIR_HOST)/bin/
endef

define Host/Clean
	rm -f $(STAGING_DIR_HOST)/bin/bsdtar
	rm -f $(STAGING_DIR_HOST)/bin/bsdcat
endef

$(eval $(call HostBuild))
