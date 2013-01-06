DEBUG ?= 0

ECHO = /bin/echo
CPP = g++

CPPFLAGS = -Wall

INCS = -Isrc
TEST_INCS = -Itest/test
TEST_SRC := $(wildcard test/*.cpp)
TEST_OBJ = $(TEST_SRC:.cpp=.test)

%.o: %.cpp
	@${ECHO} "CPP  " $<
	@${CPP} -c ${CPPFLAGS} ${INCS} -o $@ $<

%.test: %.cpp
	@${ECHO} "CPP  " $<
	@${CPP} ${CPPFLAGS} ${INCS} ${TEST_INCS} -o $@ $<

test: ${TEST_OBJ}
	@${ECHO} "TEST "
	@$(foreach var, $(TEST_OBJ), $(var);)

clean:
	@${ECHO} "CLEAN"
	@rm -f ${TEST_OBJ}

.PHONY: test clean