CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -g

BIN_DIR := bin
BUILD_DIR := build

RAYLIB_DIR := third_party/raylib
RAYLIB_SRC_DIR := $(RAYLIB_DIR)/src
RAYLIB_LIB := $(RAYLIB_SRC_DIR)/libraylib.a
RAYLIB_INCLUDE := -I$(RAYLIB_SRC_DIR)

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
APP_LIBS := $(RAYLIB_LIB) -lGL -lm -lpthread -ldl -lrt -lX11
else
$(error This Makefile currently supports Linux only)
endif

CPP_GOALS := $(filter %.cpp,$(MAKECMDGOALS))

ifeq ($(strip $(FILE)),)
FILE := $(firstword $(CPP_GOALS))
endif

ifeq ($(strip $(CPP_GOALS)),)
else
$(foreach goal,$(CPP_GOALS),$(eval $(goal):;@:))
endif

TARGET_NAME = $(basename $(notdir $(FILE)))
TARGET_BIN = $(BIN_DIR)/$(TARGET_NAME)
TARGET_OBJ = $(BUILD_DIR)/$(TARGET_NAME).o

.PHONY: all help submodule-init raylib build run clean distclean $(CPP_GOALS)

all: help

help:
	@echo "Usage:"
	@echo "  make build <file.cpp>"
	@echo "  make run <file.cpp>"
	@echo "  make raylib"
	@echo "  make submodule-init"

check-file:
	@if [ -z "$(FILE)" ]; then \
		echo "Usage: make build <file.cpp>"; \
		echo "   or: make run <file.cpp>"; \
		exit 1; \
	fi
	@if [ ! -f "$(FILE)" ]; then \
		echo "File '$(FILE)' not found"; \
		exit 1; \
	fi
	@case "$(FILE)" in \
		*.cpp) ;; \
		*) echo "FILE must be a .cpp file"; exit 1 ;; \
	esac

submodule-init:
	git submodule update --init --recursive --depth 1 $(RAYLIB_DIR)

$(RAYLIB_LIB):
	$(MAKE) -C $(RAYLIB_SRC_DIR) PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=STATIC

raylib: $(RAYLIB_LIB)

build: check-file $(RAYLIB_LIB)
	@mkdir -p $(BIN_DIR) $(BUILD_DIR)
	@obj="$(TARGET_OBJ)"; \
	bin="$(TARGET_BIN)"; \
	$(CXX) $(CXXFLAGS) $(RAYLIB_INCLUDE) -c "$(FILE)" -o "$$obj" && \
	$(CXX) $(CXXFLAGS) "$$obj" -o "$$bin" $(APP_LIBS); \
	status="$$?"; \
	rm -f "$$obj"; \
	rmdir $(BUILD_DIR) 2>/dev/null || true; \
	exit "$$status"

run: build
	@"./$(TARGET_BIN)"

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

distclean: clean
	$(MAKE) -C $(RAYLIB_SRC_DIR) clean
