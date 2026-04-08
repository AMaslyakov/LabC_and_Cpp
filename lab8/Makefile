CXX := g++
CXXFLAGS := -g -Wall -Wextra -std=c++17
BIN_DIR := bin

CPP_GOALS := $(if $(filter run with,$(MAKECMDGOALS)),,$(filter %.cpp,$(MAKECMDGOALS)))
RUN_CPP_GOALS := $(filter %.cpp,$(MAKECMDGOALS))
WITH_CPP_GOALS := $(filter %.cpp,$(MAKECMDGOALS))

ifeq ($(filter run,$(MAKECMDGOALS)),run)
ifneq ($(RUN_CPP_GOALS),)
ifeq ($(strip $(FILE)),)
FILE := $(firstword $(RUN_CPP_GOALS))
endif
$(foreach goal,$(RUN_CPP_GOALS),$(eval $(goal):;@:))
endif
endif

ifeq ($(filter with,$(MAKECMDGOALS)),with)
ifneq ($(WITH_CPP_GOALS),)
ifeq ($(strip $(FILE)),)
FILE := $(firstword $(WITH_CPP_GOALS))
endif
$(foreach goal,$(WITH_CPP_GOALS),$(eval $(goal):;@:))
endif
endif

.PHONY: all clean check-file build run with $(CPP_GOALS) $(RUN_CPP_GOALS)

all:
	@echo "Usage: make <file.cpp>"
	@echo "Example: make power.cpp"
	@echo "Run: make run power.cpp"
	@echo "Run (alt): make run FILE=power.cpp"
	@echo "With header: make with stringtype_main.cpp"

$(CPP_GOALS):
	@if [ ! -f "$@" ]; then \
		echo "File '$@' not found"; \
		exit 1; \
	fi
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c "$@" -o "$(@:.cpp=.o)"
	$(CXX) "$(@:.cpp=.o)" -o "$(BIN_DIR)/$(@:.cpp=)"
	@rm -f "$(@:.cpp=.o)"

check-file:
	@if [ -z "$(FILE)" ]; then \
		echo "Usage: make run <file.cpp>"; \
		echo "   or: make run FILE=<file.cpp>"; \
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

check-with-file:
	@if [ -z "$(FILE)" ]; then \
		echo "Usage: make with stringtype_main.cpp"; \
		echo "   or: make with FILE=stringtype_main.cpp"; \
		exit 1; \
	fi
	@if [ ! -f "$(FILE)" ]; then \
		echo "File '$(FILE)' not found"; \
		exit 1; \
	fi
	@if [ "$(FILE)" != "stringtype_main.cpp" ]; then \
		echo "With mode supports only 'stringtype_main.cpp'"; \
		exit 1; \
	fi

build: check-file
	@mkdir -p $(BIN_DIR)
	@obj="$$(basename "$(FILE)" .cpp).o"; \
	bin="$(BIN_DIR)/$$(basename "$(FILE)" .cpp)"; \
	$(CXX) $(CXXFLAGS) -c "$(FILE)" -o "$$obj"; \
	$(CXX) "$$obj" -o "$$bin"; \
	rm -f "$$obj"

run: build
	@"./$(BIN_DIR)/$$(basename "$(FILE)" .cpp)"

with: check-with-file
	@mkdir -p $(BIN_DIR)
	@bin="$$(basename "$(FILE)" .cpp)"; \
	$(CXX) $(CXXFLAGS) -c "stringtype_methods.cpp" -o "stringtype_methods.o"; \
	$(CXX) $(CXXFLAGS) -c "$(FILE)" -o "stringtype_main.o"; \
	$(CXX) "stringtype_methods.o" "stringtype_main.o" -o "$(BIN_DIR)/$$bin"; \
	rm -f "stringtype_methods.o" "stringtype_main.o"; \
	"./$(BIN_DIR)/$$bin"

clean:
	rm -f *.o
	rm -f $(basename $(wildcard *.cpp))
	rm -f $(BIN_DIR)/*
