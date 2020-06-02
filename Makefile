CFLAGS = -g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS = -ldl $(OPTLIBS)
PREFIX = /usr/local

SOURCES = $(wildcard src/**/*.c src/*.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

TEST_SRC = $(wildcard tests/*_tests.c)
TESTS = $(patsubst %.c, %, $(TEST_SRC))

TARGET = build/lib_DataStructs_Algorithms.a
SO_TARGET = $(patsubst %.a, %.so, $(TARGET))

# Compiler specification
CC = gcc

# The Target Build
all:	$(TARGET) $(SO_TARGET) tests

dev:	CFLAGS = -g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev:	all

$(TARGET):	CFLAGS += -fPIC
$(TARGET):	build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET):	$(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# The Unit Tests
.PHONY: tests
tests: LDLIBS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log

# The Install
install:	all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
check:
	@echo Files with potentially dangerous functions:
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)\|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true