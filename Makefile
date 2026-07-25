CC = clang
CFLAGS = -Wall -g -O2 -MMD -MP

BIN_DIR = ./binary
BUILD_DIR = ./build

TARGET = $(BIN_DIR)/tout

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR)

.PHONY: all clean