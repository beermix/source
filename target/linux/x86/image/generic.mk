define Device/generic
  DEVICE_TITLE := Generic x86
  DEVICE_PACKAGES += kmod-pcnet32 kmod-forcedeth
  GRUB2_VARIANT := generic
endef
TARGET_DEVICES += generic
