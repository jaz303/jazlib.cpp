DEBUG ?= 0

JAZLIB_VERSION		:= "0.0.1"
JAZLIB_BUILD_DATE	:= `date +%Y-%m-%d`

ECHO = /bin/echo
CPP = g++

CPPFLAGS = -Wall

INCS = -Isrc
TEST_INCS = -Itest/test
TEST_SRC := $(wildcard test/*.cpp)
TEST_OBJ = $(TEST_SRC:.cpp=.test)
CONFIG = src/config/config.hpp

%.o: %.cpp
	@$(ECHO) "CPP   " $<
	@$(CPP) -c $(CPPFLAGS) $(INCS) -o $@ $<

%.test: %.cpp $(CONFIG)
	@$(ECHO) "CPP   " $<
	@$(CPP) $(CPPFLAGS) $(INCS) $(TEST_INCS) -o $@ $<
	
all:
	@$(ECHO) "ALL   "

test: $(TEST_OBJ)
	@$(ECHO) "TEST  "
	@$(foreach var, $(TEST_OBJ), $(var);)
	
$(CONFIG):
	@$(ECHO) "CREATE" $@
	@$(ECHO) "#define JAZLIB_VERSION    \"$(JAZLIB_VERSION)\"" > $@
	@$(ECHO) "#define JAZLIB_BUILD_DATE \"$(JAZLIB_BUILD_DATE)\"" >> $@

rebuild: clean all
	
retest: clean test

todo:
	@grep -rInso 'TODO: \(.\+\)' src
	
clean:
	@$(ECHO) "CLEAN "
	@rm -f $(TEST_OBJ)
	@rm -f src/config/config.hpp

.PHONY: test clean rebuild retest