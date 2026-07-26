CC = clang

WARNINGS = -Wall -Wextra -Wpedantic
DEBUG_FLAGS = -g -O0
RELEASE_FLAGS = -O2 -DNDEBUG
SAN_FLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer
DEPFLAGS = -MMD -MP

CFLAGS = $(WARNINGS) $(DEBUG_FLAGS) $(DEPFLAGS)

BIN_DIR = binary
BUILD_DIR = build

TARGET = $(BIN_DIR)/tout

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

release: CFLAGS = $(WARNINGS) $(RELEASE_FLAGS) $(DEPFLAGS)
release: clean all
	strip $(TARGET)

sanitize: CFLAGS += $(SAN_FLAGS)
sanitize: LDFLAGS += $(SAN_FLAGS)
sanitize: clean all

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

-include $(DEPS)

.PHONY: all release sanitize clean