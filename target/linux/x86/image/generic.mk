define Device/generic
  DEVICE_TITLE := Generic x86
  DEVICE_PACKAGES += kmod-3c59x kmod-8139too kmod-pcnet32 kmod-r8169
endef
TARGET_DEVICES += generic
