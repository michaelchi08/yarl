include $(PWD)/config.mk
SRCS := $(shell find . -name "*.cpp")
OBJS := $(SRCS:./%.cpp=$(TESTS_DIR)/%.o)
SUBDIRS := $(addprefix $(TESTS_DIR)/, $(shell find . -type d -printf '%P\n'))

all: prep_build_dirs $(BIN_DIR)/test_runner

prep_build_dirs:
	mkdir -p $(SUBDIRS)

.SECONDEXPANSION:
$(TESTS_DIR)/%.o: ./%.cpp | $$(@D)
	$(MAKE_TEST)

$(BIN_DIR)/test_runner: $(OBJS) $(LIB_DIR)/$(LIB_NAME).a
	$(MAKE_TEST_RUNNER)
