define Device/generic
  DEVICE_TITLE := Generic x86/Geode
  DEVICE_PACKAGES += kmod-crypto-cbc
  GRUB2_VARIANT := legacy
endef
TARGET_DEVICES += generic

define Device/geos
  $(call Device/generic)
  DEVICE_TITLE := Traverse Technologies Geos
  DEVICE_PACKAGES += kmod-usb-ohci-pci linux-atm
endef
TARGET_DEVICES += geos
