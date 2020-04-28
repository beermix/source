#
# Copyright (C) 2006-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=cmake
PKG_VERSION:=3.17.2
PKG_CPE_ID:=cpe:/a:kitware:cmake

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://fossies.org/linux/misc/ \
		https://cmake.org/files/v3.17/
PKG_HASH:=fc77324c4f820a09052a7785549b8035ff8d3461ded5bbd80d252ae7d1cd3aa5

HOST_BUILD_PARALLEL:=1
HOST_CONFIGURE_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

# Workaround for GCC versions below 6.X and ccache
# Reference: https://github.com/openwrt/openwrt/pull/1929
GCC_DMPVER_GREPCMD := grep -E '^(4\.[8-9]|[5]\.?)'
GCC_DMPVER_STRING := $(shell $(HOSTCC_NOCACHE) -dumpversion | $(GCC_DMPVER_GREPCMD))
ifneq ($(GCC_DMPVER_STRING),)
  ifeq ($(CONFIG_CCACHE),y)
    $(info GCC version less than 6.0 detected, disabling CCACHE)
    HOST_CONFIGURE_VARS:=$(filter-out CC=% gcc%",$(HOST_CONFIGURE_VARS)) CC="$(HOSTCC_NOCACHE)"
    HOST_CONFIGURE_VARS:=$(filter-out CXX=% g++%",$(HOST_CONFIGURE_VARS)) CXX="$(HOSTCXX_NOCACHE)"
      else
    $(info GCC version greater or equal to 6.0 detected, no workaround set for CCACHE)
  endif
endif

HOST_CONFIGURE_VARS += \
	MAKEFLAGS="$(HOST_JOBS)" \
	CXXFLAGS="$(HOST_CFLAGS)"

HOST_CONFIGURE_ARGS := \
	$(if $(MAKE_JOBSERVER),--parallel="$(MAKE_JOBSERVER)") \
	--prefix=$(STAGING_DIR_HOST)

ifneq ($(findstring c,$(OPENWRT_VERBOSE)),)
  HOST_MAKE_FLAGS += VERBOSE=1
endif

$(eval $(call HostBuild))
