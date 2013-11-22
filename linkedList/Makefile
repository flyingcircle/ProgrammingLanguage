program_NAME := linkedList 
program_C_SRCS := $(wildcard *.c)
program_C_OBJS := ${program_C_SRCS:.c=.o}
program_OBJS := $(program_C_OBJS)
#program_INCLUDE_DIRS = lexicalAnalyzer
#program_LEXER_SOURCES = lexicalAnalyzer/lexeme.o lexicalAnalyzer/lexer.o

CFLAGS += -Wall
#CFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I $(includedir))
#CFLAGS += -std=c99

.PHONY: all test run clean distclean

all: $(program_NAME)

test: all

run: test

subdir:
	$(foreach dependency, $(SUB_DIR), $(MAKE) -C dependency)

$(program_NAME): $(program_C_OBJS)
#	$(CC) $(CFLAGS) -c $(program_LEXER_SOURCES) $(program_OBJS) 

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)

distclean: clean
