program_NAME := scanner
program_C_SRCS := $(wildcard *.c)
program_OBJS := ${program_C_SRCS:.c=.o}
program_INCLUDE_DIRS :=
program_LIBRARY_DIRS :=
program_LIBRARIES :=

CFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
#CFLAGS += -std=c99
CFLAGS += -Wall
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))

.PHONY: all test run clean distclean

all: $(program_NAME)

test: all
	-./scanner program.txt

run: test

$(program_NAME): $(program_OBJS)
	$(LINK.cc) -Wall $(program_OBJS) -o $(program_NAME)

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)

distclean: clean
