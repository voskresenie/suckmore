PKG := dwm
VERSION := 6.5
REVISION := 1

BUILD_DIR := ./build
# SRC_DIR := ./src
SRC_DIR := $(XDG_SRC_HOME)/$(PKG)

# ORIG_BUILD_DIR := $(BUILD_DIR)/$(PKG).orig
# NEW_BUILD_DIR := $(BUILD_DIR)/$(PKG).new

# ORIG_SRC_DIR := $(SRC_DIR)/$(PKG)-$(VERSION).orig
# NEW_SRC_DIR := $(SRC_DIR)/$(PKG)-$(VERSION).new

ORIG_SRC_DIR := $(SRC_DIR)/$(PKG)-$(VERSION)
ORIG_BUILD_DIR := $(BUILD_DIR)/$(PKG).orig
NEW_SRC_DIR := $(SRC_DIR)/$(PKG)-$(VERSION).new
NEW_BUILD_DIR := $(BUILD_DIR)/$(PKG).new

SOURCE_PATCH := $(PKG).voskarch.patch
BUILD_PATCH := $(PKG).PKGBUILD.voskarch.patch
PATCH_ORIG := orig
PATCH_NEW := new

FILES = dwm.c config.h drw.c drw.h
TARGET_FILES = $(foreach f,$(FILES),$(NEW_SRC_DIR)/$(f))

CLEAN_TARGETS = clean clean-src clean-build clean-new clean-orig clean-new-src clean-orig-src clean-new-build clean-orig-build

.PHONY: all install build files patch setup mod sourcedir builddir base extract fetch $(CLEAN_TARGETS)

# build targets
all: build install
	@echo TARGET:$@

install:
	@echo TARGET:$@
	@echo Installing $(PKG) $(VERSION)...
	makepkg -iD $(NEW_BUILD_DIR)

build: sourcedir files
	@echo TARGET:$@
	@echo Building $(PKG) $(VERSION)...
	makepkg -efD $(NEW_BUILD_DIR)

files: $(TARGET_FILES)
$(TARGET_FILES): $(NEW_SRC_DIR)/%: %
	@echo TARGET:$@
	@echo Comparing file... $^
	@diff -aur --color=always  $@  $^  || cp $^  $@

patch: $(BUILD_PATCH) $(SOURCE_PATCH)
	@echo TARGET:$@

# TODO: potentially use something like... $(ORIG_SRC_DIR)/$(FILES)
source-patch: $(SOURCE_PATCH)
$(SOURCE_PATCH): $(ORIG_SRC_DIR) $(NEW_SRC_DIR)
	@echo TARGET:$@
	@echo Generating $(PKG) source patch...
	# TODO: find way of stripping path from patch. Maybe symlink directory to `a` and `b` and diff?
	@echo Symlinking source directories...
	@ln -sT $(ORIG_SRC_DIR) $(PATCH_ORIG) && echo Symlinked $(ORIG_SRC_DIR) to $(PATCH_ORIG)
	@ln -sT  $(NEW_SRC_DIR)  $(PATCH_NEW) && echo Symlinked  $(NEW_SRC_DIR) to  $(PATCH_NEW)
	@#diff -aur $(ORIG_SRC_DIR) $(NEW_SRC_DIR) > $(SOURCE_PATCH)
	@diff -aur $(PATCH_ORIG)/ $(PATCH_NEW)/ > $(SOURCE_PATCH) \
		&& echo "No differences found, skipping..." || echo "Patch written to $(SOURCE_PATCH)"
	@echo Cleaning up symlinks...
	@unlink $(PATCH_ORIG)
	@unlink  $(PATCH_NEW)

build-patch: $(BUILD_PATCH)
$(BUILD_PATCH): $(ORIG_BUILD_DIR) $(NEW_BUILD_DIR)
	@echo TARGET:$@
	@echo Generating $(PKG) build patch...
	# TODO: find way of stripping path from patch. Maybe symlink directory to `a` and `b` and diff?
	@echo Symlinking build directories...
	@ln -sT $(ORIG_BUILD_DIR) $(PATCH_ORIG) && echo Symlinked $(ORIG_BUILD_DIR) to $(PATCH_ORIG)
	@ln -sT  $(NEW_BUILD_DIR)  $(PATCH_NEW) && echo Symlinked  $(NEW_BUILD_DIR) to  $(PATCH_NEW)
	@#diff -aur $(ORIG_BUILD_DIR)/PKGBUILD $(NEW_BUILD_DIR)/PKGBUILD > $(BUILD_PATCH)
	@diff -aur $(PATCH_ORIG)/PKGBUILD $(PATCH_NEW)/PKGBUILD > $(BUILD_PATCH) \
		&& echo "No differences found, skipping..." || echo "Patch written to $(BUILD_PATCH)"
	@echo Cleaning up symlinks...
	@unlink $(PATCH_ORIG)
	@unlink  $(PATCH_NEW)

# setup targets
setup: base mod
	@echo TARGET:$@

# set up modded dwm
mod: builddir sourcedir $(FILES)
	@echo TARGET:$@
	@touch $(FILES)

$(FILES):
	@echo TARGET:$@
	@test -f ../$(PKG).$(@:$(PKG).%=%) \
		&& ln -sT ../$(PKG).$(@:$(PKG).%=%) $@ && echo Symlinked ../$(PKG).$(@:$(PKG).%=%) to $@ \
		|| echo File ../$(PKG).$(@:$(PKG).%=%) not found!

sourcedir: $(NEW_SRC_DIR)
	@echo TARGET:$@
$(NEW_SRC_DIR): $(NEW_BUILD_DIR)
	@echo TARGET:$@
	@echo Setting up source directory for $(PKG) $(VERSION)...
	test -d $(NEW_SRC_DIR) || makepkg -odD $(NEW_BUILD_DIR)

builddir: $(NEW_BUILD_DIR)
	@echo TARGET:$@
$(NEW_BUILD_DIR): $(ORIG_BUILD_DIR)
	@echo TARGET:$@
	@echo Duplicating $(PKG) build directory...
	@cp -rT $(ORIG_BUILD_DIR) $(NEW_BUILD_DIR)
	@echo Applying PKGBUILD patch...
	@test -f $(BUILD_PATCH) && patch -d $(NEW_BUILD_DIR) -Np1 -i ../../$(BUILD_PATCH)
	@# # test -f $(PKG).PKGBUILD.voskarch.patch && patch -d $(NEW_BUILD_DIR) -Np1 -i $(PKG).PKGBUILD.voskarch.patch

# set up base (vanilla) dwm
base: fetch extract
	@echo TARGET:$@

# extract:
# 	@echo Extracting $(PKG) $(VERSION)...
# 	makepkg -odD $(ORIG_BUILD_DIR)

extract: $(ORIG_SRC_DIR)
	@echo TARGET:$@
$(ORIG_SRC_DIR): $(ORIG_BUILD_DIR)
	@echo TARGET:$@
	@echo Extracting $(PKG) $(VERSION)...
	makepkg -odD $(ORIG_BUILD_DIR)

# fetch:
# 	@echo Fetching $(PKG) from AUR...
# 	test -d $(ORIG_BUILD_DIR) || git clone https://aur.archlinux.org/$(PKG).git $(ORIG_BUILD_DIR)

fetch: $(ORIG_BUILD_DIR)
	@echo TARGET:$@
$(ORIG_BUILD_DIR):
	@echo TARGET:$@
	@echo Fetching $(PKG) from AUR...
	test -d $(ORIG_BUILD_DIR) || git clone https://aur.archlinux.org/$(PKG).git $(ORIG_BUILD_DIR)

# clean targets
clean: clean-src clean-build

clean-src: clean-new-src clean-orig-src
	@echo Removing source dir if empty...
	rmdir --ignore-fail-on-non-empty $(SRC_DIR)
clean-build: clean-new-build clean-orig-build
	@echo Removing build dir if empty...
	rmdir --ignore-fail-on-non-empty $(BUILD_DIR)

clean-new: clean-new-src clean-new-build
clean-orig: clean-orig-src clean-orig-build

clean-new-src:
	@echo Removing modified source dir...
	rm -rf $(NEW_SRC_DIR)
clean-orig-src:
	@echo Removing base source dir...
	rm -rf $(ORIG_SRC_DIR)

clean-new-build:
	@echo Removing modified build dir...
	rm -rf $(NEW_BUILD_DIR)
clean-orig-build:
	@echo Removing base build dir...
	rm -rf $(ORIG_BUILD_DIR)
