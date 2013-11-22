SUB_DIR := ../parser ../lexicalAnalyzer
program_NAME := environment
program_C_SRCS := $(wildcard *.c)
program_C_OBJS := ${program_C_SRCS:.c=.o}
program_OBJS := $(program_C_OBJS)
program_INCLUDE_DIRS = ../lexicalAnalyzer ../parser
program_LEXER_SOURCES = ../lexicalAnalyzer/lexeme.o ../lexicalAnalyzer/lexer.o ../lexicalAnalyzer/types.o \
../parser/parser.o

CFLAGS += -Wall
CFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I $(includedir))
#CFLAGS += -std=c99

.PHONY: all test run clean distclean

all: subdir $(program_NAME)

test: all

run: test

subdir:
	$(foreach dependency, $(SUB_DIR), $(MAKE) -C $(dependency);)

$(program_NAME): $(SUB_DIR) $(program_C_OBJS)
	$(CC) $(CFLAGS) $(program_LEXER_SOURCES) $(program_OBJS) -o $(program_NAME) 

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)
	$(MAKE) -C $(SUB_DIR) clean

distclean: clean
