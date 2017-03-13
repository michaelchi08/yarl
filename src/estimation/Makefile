include $(PWD)/config.mk
OUTPUT_DIR = $(OBJ_DIR)/$(notdir $(shell pwd))
SRCS = $(wildcard *.cpp)
OBJS = $(addprefix $(OUTPUT_DIR)/, $(SRCS:.cpp=.o))

default: $(OUTPUT_DIR) $(OBJS)

$(OUTPUT_DIR):
	mkdir $(OUTPUT_DIR)

$(OUTPUT_DIR)/%.o: %.cpp
	$(MAKE_OBJ)
