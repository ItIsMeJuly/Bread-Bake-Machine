PRODUCT=breadbake

CFLAGS=-Wall -Werror -Wextra -pedantic -ggdb -O0 -Iproduct -Iproduct/interfaces -std=c++17

SOURCES=$(wildcard product/*.cpp)
HEADERS=$(wildcard product/*.h) \
        $(wildcard product/interfaces/*.h)

LIBS=-lpthread

TEST=test_$(PRODUCT)
TEST_SOURCES=$(filter-out product/main.cpp, $(SOURCES)) \
	     $(wildcard test/*.cpp)
TEST_HEADERS=$(HEADERS) \
             $(wildcard test/*.h)
			 
TEST_LIBS=-lgtest -lgmock -lgmock_main $(LIBS)

CC=g++

.phony: all clean test klocwork klocwork_after_makefile_change

all: $(PRODUCT)

$(PRODUCT): $(SOURCES) $(HEADERS) Makefile
	@$(CC) $(CFLAGS) $(SOURCES) -o $@ $(LIBS)

$(TEST): $(TEST_SOURCES) $(TEST_HEADERS) Makefile
	@$(CC) $(CFLAGS) -Itest $(TEST_SOURCES) -o $@ $(TEST_LIBS)

clean:
	@rm -rf $(PRODUCT) $(TEST)
	@rm -rf kwinject.out .kwlp .kwps

test: $(TEST)
	@./$(TEST)

klocwork:
	@kwcheck run

klocwork_after_makefile_change: clean
	@/opt/klocwork/kwenv.sh
	@kwcheck run
