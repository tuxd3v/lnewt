## Lua-dev Newt-dev Dependencies Related
#
DEPS		:= lua5.3 -lnewt
ifeq ($(MAKECMDGOALS),)
MAKECMDGOALS := all
endif

## Lnewt Shared Library 
#
NAME		:= lnewt
MAJOR		:= 0
MINOR		:= 52
FIX		:= 20
VERSION		:= $(MAJOR).$(MINOR).$(FIX)


ifeq ($(MAKECMDGOALS), all)
# Lua-dev header PATHs
IDIR		:= /usr/include/lua5.3
ifeq (,$(wildcard $(IDIR)/.))
$(error Lua Include Folder: $(IDIR), **NOT Detected**, ABORTING..)
endif

## Platform/OS/Machine
ifndef PLATFORM
PLATFORM	:= $(if $(shell uname | egrep -Ei linux),linux,android)
ifeq ($(PLATFORM),linux)
$(info ** PLATFORM = $(PLATFORM)  **)
else ifeq ($(PLATFORM),android)
$(info ** PLATFORM = $(PLATFORM)  **)
else
$(error ** PLATFORM = $(PLATFORM) **,Invalid platform type..)
endif
LONG_BIT	:= $(shell getconf LONG_BIT)
$(info ** OS       = $(LONG_BIT)Bits **)
ifdef MACHINE
      MACHINE :=
      undefine MACHINE
endif
MACHINE		:= $(shell uname -m)
endif
endif

ifeq ($(MAKECMDGOALS),all)
 # Compiller Options
CC		:= gcc
 # Arch/Tune/ Linker Options
ifdef ARCH
override undefine ARCH
endif
ifeq ($(LONG_BIT),32)
ARCH		:=$(shell unset ARCH;gcc -dumpmachine|cut -d- -f 1)
#ARCH		:=$(if $(findstring nil,$(ARCH)),,$(ARCH))
ARCH		:=$(if $(findstring x86,$(MACHINE)),i386,$(ARCH))
ARCH		:=$(if $(findstring i686,$(MACHINE)),i386,$(ARCH))
ARCH		:=$(if $(findstring aarch64,$(MACHINE)),armv7-a,$(ARCH))
ARCH		:=$(if $(findstring android,$(MACHINE)),armv7,$(ARCH))
$(info ** ARCH     = $(ARCH) **)
TUNE		:=$(shell ${PWD}/aarch mtune)
TUNE		:=$(if $(findstring nil,$(TUNE)),,$(TUNE))
else ifeq ($(LONG_BIT),64)
ARCH		:=$(shell unset ARCH;${PWD}/aarch march)
#ARCH		:=$(if $(findstring nil,$(ARCH)),,$(ARCH))
ARCH		:=$(if $(findstring x86,$(MACHINE)),x86-64,$(ARCH))
ARCH		:=$(if $(findstring android,$(MACHINE)),armv7,$(ARCH))
$(info ** ARCH     = $(ARCH) **)
TUNE		:=$(shell ${PWD}/aarch mtune)
TUNE		:=$(if $(findstring nil,$(TUNE)),,$(TUNE))
endif
ifeq ($(ARCH),nil)
$(warning ** ARCH     = $(ARCH) **,Unknown Arch type..)
$(info ** ARCH    = native **, Will be used..)
ARCH := native
endif

ifdef TUNE
$(info ** TUNE     = $(TUNE) **)
CFLAGS		:= -march=$(ARCH) -mtune=$(TUNE) -fPIC -Wall -Werror -DLUA_C89_NUMBERS -O3 -I$(IDIR) # Compiler Flags
TEST_CFLAGS	:= -march=$(ARCH) -mtune=$(TUNE) -DLUA_C89_NUMBERS -O3 -g -I$(IDIR)
else
CFLAGS		:= -march=$(ARCH) -fPIC -Wall -Werror -DLUA_C89_NUMBERS -O3 -I$(IDIR) # Compiler Flags
TEST_CFLAGS	:= -march=$(ARCH) -DLUA_C89_NUMBERS -O3 -g -I$(IDIR)
endif
LDFLAGS		:= -shared -Wl,-soname,$(NAME).so.$(MAJOR) -l$(DEPS) # Linker Flags
TEST_LDFLAGS	:= -L/usr/lib/aarch64-linux-gnu -l$(DEPS) -lm -ldl
# end makegoals
endif

## LNEWT source/headers.. Code Related
LNEWT_SRCS	:= lnewt.c
LNEWT_HDRS	:= lnewt.h
DEBUG_SRCS	:= debug.c
DEBUG_HDRS	:= $(DEBUG_SRCS:.c=.h)

TEST_SRCS	:= test.c
TEST_HDRS	:= $(LNEWT_HDRS)


# Objects
#OBJS		:= $(SRCS:.c=.o)
LNEWT_OBJS	:= $(LNEWT_SRCS:.c=.o)
DEBUG_OBJS	:= $(DEBUG_SRCS:.c=.o)

TEST_OBJS	:= $(TEST_SRCS:.c=.o)

## ATS Installation ENVIRONMENT PATHs
#
ifeq ($(MAKECMDGOALS),install)
	# Shared Library Module
ifndef LDIR
LDIR		:= /usr/local/lib/lua/5.3
endif
endif
## Binaries
#TEST
TEST_BIN	:= main

# project c/h/lua  relative paths
SRCS_PATH	:= src
HDRS_PATH	:= include
# Project c/h relative paths.to/file.name
LNEWT_SRCS	:= $(addprefix $(SRCS_PATH)/,$(LNEWT_SRCS))
LNEWT_HDRS	:= $(addprefix $(HDRS_PATH)/,$(LNEWT_HDRS))
DEBUG_SRCS	:= $(addprefix $(SRCS_PATH)/,$(DEBUG_SRCS))
DEBUG_HDRS	:= $(addprefix $(HDRS_PATH)/,$(DEBUG_HDRS))
# for testing ats purposes( with a C frontend.. )
TEST_HDRS	:= $(addprefix $(HDRS_PATH)/,$(TEST_HDRS))

# TARGETs
.PHONY: all
all   : $(NAME).so.$(VERSION)

$(LNEWT_OBJS): $(LNEWT_SRCS) $(LNEWT_HDRS)
	$(CC) -c $(CFLAGS) -o $@ $<


$(NAME).so.$(VERSION): $(LNEWT_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY: install
install:
	$(info Install new LNEWT Library .........: ${NAME}.so.${VERSION} in '${LDIR}')
	@install --preserve-timestamps --owner=root --group=root --mode=444 --target-directory=${LDIR} ${NAME}.so.${VERSION}
	$(info Check Lua SymLink Path, if exist...: $ '/usr/local/lib/lua/5.3')
	@if [ ! -d /usr/local/lib/lua/5.3 ];then	\
		mkdir -pv /usr/local/lib/lua/5.3;		\
	fi	
	$(info Creating soname symLink ...........: ${NAME}.so in '/usr/local/lib/lua/5.3')
	@if [ -L /usr/local/lib/lua/5.3/lnewt.so ];then	\
		rm /usr/local/lib/lua/5.3/lnewt.so;		\
	fi
	@ln -s $(LDIR)/$(NAME).so.$(VERSION) /usr/local/lib/lua/5.3/lnewt.so

.PHONY: clean
clean:
	rm -f $(NAME).o $(NAME).so.$(VERSION)
