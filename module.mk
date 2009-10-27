MODULE := engines/dgds

MODULE_OBJS = \
	bmp.o \
	compression.o \
	detection.o \
	dgds.o \
	font.o \
	game.o \
	palette.o \
	resource.o \
	resourcemanager.o \
	test.o

# This module can be built as a plugin
ifdef BUILD_PLUGINS
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
