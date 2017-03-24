include $(PWD)/config.mk

SRCS := $(shell find . -name "*.cpp")
OBJS := $(SRCS:./%.cpp=$(OBJ_DIR)/%.o)
SUBDIRS := $(addprefix $(OBJ_DIR)/, $(shell find . -type d -printf '%P\n'))

.PHONY: all prep_build_dirs

all: prep_build_dirs $(LIB_DIR)/$(LIB_NAME).a

prep_build_dirs:
	mkdir -p $(SUBDIRS)

.SECONDEXPANSION:
$(OBJ_DIR)/%.o: ./%.cpp | $$(@D)
	$(MAKE_OBJ)

$(LIB_DIR)/$(LIB_NAME).a: $(OBJS)
	$(MAKE_STATIC_LIB)
