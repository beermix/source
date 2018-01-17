Package/amd64-microcode = $(call Package/firmware-default,AMD64 CPU microcode)
define Package/amd64-microcode/install
	$(INSTALL_DIR) $(1)/lib/firmware/amd-ucode
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/amd-ucode/microcode_amd.bin $(1)/lib/firmware/amd-ucode
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/amd-ucode/microcode_amd_fam15h.bin $(1)/lib/firmware/amd-ucode
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/amd-ucode/microcode_amd_fam16h.bin $(1)/lib/firmware/amd-ucode
endef
$(eval $(call BuildPackage,amd64-microcode))

