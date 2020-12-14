define Host/Configure
	true
endef

define Host/Compile
	true
endef

define Host/Install
	sh $(RUST_INSTALL_BINARIES)
endef
