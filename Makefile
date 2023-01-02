BUILD_DIR=build
BIN=$(BUILD_DIR)/learn


all: $(BUILD_DIR)
	meson compile -v -C $(BUILD_DIR)

$(BUILD_DIR):
	meson setup $(BUILD_DIR)

run: all
	./$(BIN)	

debug: all
	gdb $(BIN)

clean:
	rm -rf $(BUILD_DIR)
