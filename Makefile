.PHONY: clean

CXXFLAGS += -std=c++2a -ggdb
WARNING += -pedantic -Wall -Wextra -Werror -Wcast-align -Wcast-qual							\
-Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self							\
-Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast									\
-Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo	\
-Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused								\
-Wzero-as-null-pointer-constant
SANITIZERS += -fsanitize=address -fsanitize=thread -fsanitize=leak	\
-fsanitize=undefined

SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
DEPENDS := $(patsubst %.cpp,%.d,$(SOURCES))

clean:
	$(RM) -r build $(OBJECTS) $(DEPENDS)

build:
	mkdir -p build

-include $(DEPENDS)

%.o: %.cpp Makefile
	$(CXX) $(WARNING) $(CXXFLAGS) $(SANITIZER) -MMD -MP -c $< -o $@

build/test: $(OBJECTS) build
	$(CXX) $(WARNING) $(CXXFLAGS) $(OBJECTS) -o $@

test: build/test
	./build/test
