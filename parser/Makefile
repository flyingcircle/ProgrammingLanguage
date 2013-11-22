SUB_DIR := ../lexicalAnalyzer
program_NAME := recognizer
program_C_SRCS := $(wildcard *.c)
program_C_OBJS := ${program_C_SRCS:.c=.o}
program_OBJS := $(program_C_OBJS)
program_INCLUDE_DIRS = ../lexicalAnalyzer
program_LEXER_SOURCES = ../lexicalAnalyzer/lexeme.o ../lexicalAnalyzer/lexer.o

CFLAGS += -Wall
CFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I $(includedir))
#CFLAGS += -std=c99

.PHONY: all test run clean distclean

all: subdir $(program_NAME)

test: all
	-./recognizer ./testFiles/program.txt
	-./recognizer ./testFiles/MissingPeriod.txt
	-./recognizer ./testFiles/noEndingBlock.txt
	-./recognizer ./testFiles/nestedFunctionCall.txt

run: test

subdir:
	$(MAKE) -C $(SUB_DIR)

$(program_NAME): $(SUB_DIR) $(program_C_OBJS)
	$(CC) $(CFLAGS) $(program_LEXER_SOURCES) $(program_OBJS) -o $(program_NAME) 

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)
	$(MAKE) -C $(SUB_DIR) clean

distclean: clean
