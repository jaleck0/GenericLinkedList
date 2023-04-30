ASSIGNMENT=linkedlist
ASSIGNMENT_TEST=$(ASSIGNMENT)_test

UNITY_FOLDER=./Unity
INC_DIRS=-Iproduct
TEST_INC_DIRS=$(INC_DIRS) -I$(UNITY_FOLDER)

SHARED_FILES=product/linked_list.c

ASSIGNMENT_FILES=$(SHARED_FILES) \
	      product/main.c \
	      product/memory.c \
	      product/terminal_io.c

ASSIGNMENT_TEST_FILES=$(SHARED_FILES) \
	           $(UNITY_FOLDER)/unity.c \
	           test/empty_test.c

HEADER_FILES=product/*.h

CC=gcc

SYMBOLS=-g  -O0 -std=c99 -Wall -Wextra -Werror
TEST_SYMBOLS=$(SYMBOLS) -DTEST

.PHONY: clean test klocwork klocwork_after_makefile_change

all: $(ASSIGNMENT)

$(ASSIGNMENT): Makefile $(ASSIGNMENT_FILES)  $(HEADER_FILES)
	$(CC) $(INC_DIRS) $(SYMBOLS) $(ASSIGNMENT_FILES) -o $(ASSIGNMENT)

$(ASSIGNMENT_TEST): Makefile $(ASSIGNMENT_TEST_FILES)  $(HEADER_FILES)
	$(CC) $(TEST_INC_DIRS) $(TEST_SYMBOLS) $(ASSIGNMENT_TEST_FILES) -o $(ASSIGNMENT_TEST)

clean:
	@rm -f $(ASSIGNMENT) $(ASSIGNMENT_TEST)
	@rm -rf kwinject.out .kwlp .kwps

test: $(ASSIGNMENT_TEST)
	  @valgrind ./$(ASSIGNMENT_TEST)

klocwork:
	@kwcheck run

klocwork_after_makefile_change: clean
	@/opt/klocwork/kwenv.sh
	@kwcheck run
