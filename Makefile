# Library name
NAME := gnl.a

# Compiler and flags
CC        := clang
CFLAGS    := -Wall -Wextra -Werror -Wshadow -Wpedantic -Wconversion -Wdouble-promotion -std=c17
DEPSFLAGS := -MMD -MP

# Compilation mode (default: release)
MODE ?= release

ifeq ($(MODE),debug)
    CFLAGS += -g3 -fno-omit-frame-pointer
else ifeq ($(MODE),release)
    CFLAGS += -O2
endif

# Directories
SRCDIR := src
OBJDIR := obj
SRCFILES := $(SRCDIR)/gnl.c $(SRCDIR)/gnl_utils.c

# Object files and dependencies
SRCOBJ := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCFILES))
DEPS   := $(SRCOBJ:.o=.d)

# Headers
HEADERS := -I include

# Archive command
AR := ar
ARFLAGS := rcs

# Colors for status messages
BLUE := \033[36m
NC   := \033[0m

# Build rules
.PHONY: all
all: $(NAME)  ## Build the library (default)

.PHONY: debug
debug: MODE = debug
debug: $(NAME)  ## Build in debug mode

.PHONY: clean
clean:  ## Clean object files
	@rm -rf $(OBJDIR)
	@echo "Cleaned object files"

.PHONY: fclean
fclean: clean  ## Clean everything
	@rm -f $(NAME)
	@echo "Cleaned everything"

.PHONY: re
re: fclean all  ## Rebuild everything

# .PHONY: test
# test: $(NAME)
# 	@echo "Running tests..."
# 	@./run_tests.sh

.PHONY: format
format:  ## Format code via clang-format
	clang-format -i $(SRCFILES) include/*.h
	@echo "Code formatted!"

.PHONY: compdb
compdb: clean  ## Generate compile_commands.json using Bear
	@rm -f compile_commands.json
	@echo "Running Bear with make -j$(shell nproc)"
	bear -- make -j$(shell nproc)
	@echo "Generated compile_commands.json"

.PHONY: help
help:  ## Display this help message
	@echo 'Usage: make $(BLUE)<target>$(NC)'
	@echo 'Available targets:'
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "  $(BLUE)%-15s$(NC) %s\n", $$1, $$2}' $(MAKEFILE_LIST)

# Build library
$(NAME): $(SRCOBJ)
	$(AR) $(ARFLAGS) $@ $(SRCOBJ)
	@echo "Library: '$(NAME)' built successfully"

# Rule for compiling source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@echo "Compiling $< -> $@"
	$(CC) $(CFLAGS) $(DEPSFLAGS) $(HEADERS) -c $< -o $@

# Create base object directory if it doesn't exist
$(OBJDIR):
	@mkdir -p $@

# Include dependency files
-include $(DEPS)
