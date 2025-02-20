# Library name
NAME := gnl.a
NAME_DEBUG := debug_$(NAME)

# compiler + default flags
CC := clang
BASE_FLAGS := -std=c17
WARNING_FLAGS := -Wall -Wextra -Werror -Wshadow -Wconversion -Wdouble-promotion -Wformat=2 -Wpedantic
CFLAGS := $(BASE_FLAGS) $(WARNING_FLAGS)
DEP_FLAGS := -MMD -MP

# build flags
DEBUG_FLAGS := -g3 -DDEBUG -fno-omit-frame-pointer -fsanitize=address
RELEASE_FLAGS := -DNDEBUG

# Compilation mode (default: debug)
MODE ?= debug

ifeq ($(MODE),debug)
    CFLAGS += -g3 -DDEBUG -fno-omit-frame-pointer -fsanitize=address
else ifeq ($(MODE),release)
    CFLAGS += -DNDEBUG
endif

# Directories
SRCDIR := src
OBJDIR := obj

OBJDIR_RELEASE := $(OBJDIR)/release
OBJDIR_DEBUG := $(OBJDIR)/debug

SRCFILES := gnl.c

# build dirs
OBJS := $(SRCFILES:%.c=$(OBJDIR_RELEASE)/%.o)
OBJS_DEBUG := $(SRCFILES:%.c=$(OBJDIR_DEBUG)/%.o)

DEPS := $(OBJS:.o=.d)
DEPS_DEBUG := $(OBJS_DEBUG:.o=.d)

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
all: $(NAME_DEBUG)  ## Build the debug library (default)

.PHONY: release
release: MODE = release
release: $(NAME)  ## Build the library

.PHONY: fmt
fmt:  ## Format code via clang-format
	find . -type f \( -name "*.c" -o -name "*.h" \) -print0 | xargs -0 clang-format -i

.PHONY: clean
clean:  ## Clean object files
	@rm -rf $(OBJDIR)

.PHONY: fclean
fclean: clean  ## Clean everything
	@rm -f $(NAME) $(NAME_DEBUG)

.PHONY: re
re: fclean all  ## Rebuild everything

.PHONY: compdb
compdb: clean  ## Generate compile_commands.json using Bear
	@rm -f compile_commands.json
	bear -- make -j$(shell nproc)

.PHONY: help
help:  ## Display this help message
	@echo 'Usage: make $(BLUE)<target>$(NC)'
	@echo 'Available targets:'
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "  $(BLUE)%-15s$(NC) %s\n", $$1, $$2}' $(MAKEFILE_LIST)

# Build library
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(NAME_DEBUG): $(OBJS_DEBUG)
	$(AR) $(ARFLAGS) $@ $^

# create object files release
$(OBJDIR_RELEASE)/%.o: $(SRCDIR)/%.c | $(OBJDIR_RELEASE)
	$(CC) $(CFLAGS) $(DEP_FLAGS) $(HEADERS) -c $< -o $@

# create object files debug
$(OBJDIR_DEBUG)/%.o: $(SRCDIR)/%.c | $(OBJDIR_DEBUG)
	$(CC) $(CFLAGS) $(DEP_FLAGS) $(HEADERS) -c $< -o $@

# create obj and or sub folders
$(OBJDIR_RELEASE) $(OBJDIR_DEBUG):
	mkdir -p $@

# Include dependency files
-include $(DEPS) $(DEPS_DEBUG)
