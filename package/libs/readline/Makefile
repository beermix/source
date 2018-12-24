#
# Copyright (C) 2006-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=readline
PKG_VERSION:=2ebbb26fda2e37f9eb0a92373c2cdcdc9b1b7b33

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=git://git.savannah.gnu.org/readline.git
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_SOURCE_VERSION).tar.xz

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/host-build.mk

define Package/libreadline
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Command lines edition library
  URL:=http://cnswww.cns.cwru.edu/php/chet/readline/rltop.html
  ABI_VERSION:=$(PKG_VERSION)
endef

define Package/libreadline/description
	The Readline library provides a set of functions for use by applications 
	that allow users to edit command lines as they are typed in. Both Emacs 
	and vi editing modes are available. The Readline library includes 
	additional functions to maintain a list of previously-entered command 
	lines, to recall and perhaps reedit those lines, and perform csh-like 
	history expansion on previous commands.
endef

# prevent "autoreconf" from removing "aclocal.m4"
PKG_REMOVE_FILES:=

CONFIGURE_ARGS += \
	--enable-shared \
	--enable-static \
	--with-curses \

CONFIGURE_VARS += \
	bash_cv_wcwidth_broken=no \
	bash_cv_func_sigsetjmp=yes \

TARGET_CPPFLAGS:=-I. -I.. $(TARGET_CPPFLAGS)

TARGET_CFLAGS += $(FPIC)

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/readline $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/lib{history,readline}.{a,so,so.8,so.8.0} $(1)/usr/lib/
endef

define Package/libreadline/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/lib{history,readline}.{so,so.8,so.8.0} $(1)/usr/lib/
endef

$(eval $(call HostBuild))
$(eval $(call BuildPackage,libreadline))
