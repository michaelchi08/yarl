include $(PWD)/config.mk

SRCS := $(shell find . -name "*.cpp")
OBJS := $(SRCS:./%.cpp=$(OBJ_DIR)/%.o)
SUBDIRS := $(addprefix $(OBJ_DIR)/, $(shell find . -type d -printf '%P\n'))

.PHONY: all

all: prep_build_dirs libbattery

prep_build_dirs:
	mkdir -p $(SUBDIRS)

.SECONDEXPANSION:
$(OBJ_DIR)/%.o: ./%.cpp | $$(@D)
	$(MAKE_OBJ)

libbattery: $(OBJS)
	$(MAKE_STATIC_LIB)
