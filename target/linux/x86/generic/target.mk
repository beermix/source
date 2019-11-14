BOARDNAME:=Generic
CPU_TYPE :=atom
FEATURES += pci usb
DEFAULT_PACKAGES += kmod-button-hotplug

define Target/Description
	Build firmware images for modern x86 based boards with CPUs
	supporting at least the Intel Pentium 4 instruction set with
	MMX, SSE and SSE2.
endef

