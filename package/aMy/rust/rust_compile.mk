define Host/Configure
	# Required because OpenWrt Default CONFIGURE_ARGS contain extra
	# args that cause errors
	cd $(HOST_BUILD_DIR) && \
	  RUST_BACKTRACE=full ./configure $(CONFIGURE_ARGS)
endef

define Host/Compile
	cd $(HOST_BUILD_DIR) && \
	RUST_BACKTRACE=full $(PYTHON) x.py --config ./config.toml dist cargo extended \
	   library/std llvm-tools miri rust-dev rustc-dev
endef

define Host/Install
	cd $(HOST_BUILD_DIR)/build/dist && \
	   $(RM) *.gz && \
	   $(call dl_tar_pack,$(DL_DIR)/$(RUST_INSTALL_FILE_NAME),.) && \
	cd $(RUST_TMP_DIR) && \
	   $(TAR) -xJf $(DL_DIR)/$(RUST_INSTALL_FILE_NAME) && \
	   find -iname "*.xz" -exec $(TAR) -x -J -f {} ";" && \
	   find ./* -type f -name install.sh -execdir sh {} --prefix=$(CARGO_HOME) --disable-ldconfig \;
endef
