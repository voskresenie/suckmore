PKG := st
VERSION := 0.9.2
REVISION := 1

# BUILD_DIR := ./build
# SRC_DIR := ./src
# SRC_DIR := $(XDG_SRC_HOME)/$(PKG)

# BASE_BUILD_DIR := $(BUILD_DIR)/$(PKG).orig
# MOD_BUILD_DIR := $(BUILD_DIR)/$(PKG).new

# BASE_SRC_DIR := $(SRC_DIR)/$(PKG)-$(VERSION).orig
# MOD_SRC_DIR := $(SRC_DIR)/$(PKG)-$(VERSION).new

# BASE_SRC_DIR := ../src/$(PKG)/$(PKG)-$(VERSION)
BASE_SRC_DIR := $(XDG_SRC_HOME)/$(PKG)/$(PKG)-$(VERSION)
BASE_BUILD_DIR := ./build/$(PKG).orig
# SRC_DIR := ../src/$(PKG)/$(PKG)-$(VERSION).make
SRC_DIR := $(XDG_SRC_HOME)/$(PKG)/$(PKG)-$(VERSION).make
BUILD_DIR := ./build/$(PKG).new
FILES = config.h x.c

CLEAN_TARGETS = clean clean-src clean-build clean-base clean-mod clean-base-src clean-mod-src clean-base-build clean-mod-build

.PHONY: all install st files $(FILES) patch setup extract fetch $(CLEAN_TARGETS)

# build targets
all: st

install:
	@echo Installing $(PKG) $(VERSION)...
	makepkg -iD $(MOD_BUILD_DIR)

build: files
	@echo Building $(PKG) $(VERSION)...
	makepkg -efD $(MOD_BUILD_DIR)

files: $(FILES)

$(FILES):
	@echo Comparing file... $@
	@diff -aur --color=always  $(SRC_DIR)/$@  $@  || cp $@  $(SRC_DIR)/$@

patch: files
	@echo Generating $(PKG) patch...
	-diff -aur $(BASE_SRC_DIR) $(SRC_DIR) > $(PKG).voskarch.patch
	-diff -aur $(BASE_BUILD_DIR)/PKGBUILD $(MOD_BUILD_DIR)/PKGBUILD > $(PKG).PKGBUILD.voskarch.patch

# setup targets
setup: fetch extract

extract:
	@echo Extracting $(PKG) $(VERSION)...
	makepkg -odD $(BASE_BUILD_DIR)

fetch:
	@echo Fetching $(PKG) from AUR...
	git clone https://aur.archlinux.org/$(PKG).git $(BASE_BUILD_DIR)

# clean targets
clean: clean-base clean-mod

clean-src: clean-base-src clean-mod-src
clean-build: clean-base-build clean-mod-build

clean-base: clean-base-src clean-base-build
clean-mod: clean-mod-src clean-mod-build

clean-base-src:
	makepkg -cD $(BASE_BUILD_DIR)
clean-mod-src:
	makepkg -cD $(MOD_BUILD_DIR)

clean-base-build:
	rm -rf $(BASE_BUILD_DIR)
clean-mod-build:
	rm -rf $(MOD_BUILD_DIR)
