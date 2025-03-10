TARGET_EXEC := swkotor

BUILD_DIR := ./build
SRC_DIRS := ./src

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. The shell will incorrectly expand
# these otherwise, but we want to send the * directly to the find command.
SRCS := $(shell find $(SRC_DIRS) -name '*.c')

# Prepends BUILD_DIR and appends .o to every src file
# As an example, ./your_dir/hello.cpp turns into ./build/./your_dir/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CC := clang
CCFLAGS += -std=c99 -Wall -Werror -Wno-pointer-sign
LDFLAGS := $(LDFLAGS) -lm -lraylib

# The final build step.
all:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CCFLAGS) $(SRCS) -o $(BUILD_DIR)/$(TARGET_EXEC) $(LDFLAGS)

release: CCFLAGS += -O3
release: all
debug: CCFLAGS += -O0 -DDEBUG -g
debug: all
release-with-debug: CCFLAGS += -O3 -DDEBUG -g
release-with-debug: all
testing: CCFLAGS += -DIS_TESTING=1
testing: release-with-debug
testing: all

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)
