include $(PWD)/config.mk
SRCS := $(shell find . -name "*.cpp")
OBJS := $(SRCS:./%.cpp=$(TESTS_DIR)/%.o)
SUBDIRS := $(addprefix $(TESTS_DIR)/, $(shell find . -type d -printf '%P\n'))

all: prep_build_dirs test_runner

prep_build_dirs:
	mkdir -p $(SUBDIRS)

.SECONDEXPANSION:
$(TESTS_DIR)/%.o: ./%.cpp | $$(@D)
	$(MAKE_OBJ)

test_runner: $(OBJS)
	echo $(LIBS)
	$(CXX) $(CXXFLAGS) -c $@.cpp -o $(TESTS_DIR)/$@.o; \
	$(CXX) $(TESTS_DIR)/$@.o $(OBJS) -o $(BIN_DIR)/$@ $(LIBS);
