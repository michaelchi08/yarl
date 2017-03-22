include $(PWD)/config.mk

# SRCS := $(shell find . -name "*.cpp")
# OBJS := $(SRCS:./%.cpp=$(OBJ_DIR)/%.o)
# SUBDIRS := $(addprefix $(OBJ_DIR)/, $(shell find . -type d -printf '%P\n'))
#
# default: prep_build_dirs $(OBJS)
# 	echo $(OBJS)
#
# prep_build_dirs:
# 	mkdir -p $(SUBDIRS)
#
# .SECONDEXPANSION:
# %.o: %.cpp
# 	$(MAKE_OBJ)


SRC_DIR := .
DEP_DIR := dep

SRCS := $(shell find $(SRC_DIR) -name "*.cpp")
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
SUBDIRS := $(addprefix $(OBJ_DIR)/, $(shell find . -type d -printf '%P\n'))

.PHONY: all

all: prep_build_dirs $(OBJS)

prep_build_dirs:
	mkdir -p $(SUBDIRS)

.SECONDEXPANSION:
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $$(@D)
	$(MAKE_OBJ)
