# Library name
NAME := gnl.a

# Compiler and flags
CC        := clang
CFLAGS    := -Wall -Wextra -Werror -Wshadow -Wpedantic -Wconversion -Wdouble-promotion -std=c17
DEBUGFLAG := -g3 -fno-omit-frame-pointer
DEPSFLAGS := -MMD -MP

# Directories
SRCDIR := src
OBJDIR := obj
SRCFILES := $(SRCDIR)/get_next_line.c

# Object files and dependencies
SRCOBJ := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCFILES))
DEPS   := $(SRCOBJ:.o=.d)

# Headers
HEADERS := -I include

# Archive command
LIB := ar rcs

# Colors for status messages
BLUE := \033[36m
NC   := \033[0m

# Build rules
.PHONY: all
all: $(NAME)  ## Build the library (default)

.PHONY: debug
debug: CFLAGS += $(DEBUGFLAG)  ## Build with debug flags
debug: $(NAME)

.PHONY: clean
clean:  ## Clean object files
	@rm -rf $(OBJDIR)
	@echo "Cleaned object files"

.PHONY: fclean
fclean: clean  ## Clean object files and library
	@rm -f $(NAME)
	@echo "Cleaned everything"

.PHONY: re
re: fclean all  ## Clean all and rebuild

.PHONY: help
help:  ## Display this help message
	@echo 'Usage: make $(BLUE)<target>$(NC)'
	@echo 'Available targets:'
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "  $(BLUE)%-15s$(NC) %s\n", $$1, $$2}' $(MAKEFILE_LIST)

# Build library
$(NAME): $(SRCOBJ)
	$(LIB) $@ $(SRCOBJ)
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

