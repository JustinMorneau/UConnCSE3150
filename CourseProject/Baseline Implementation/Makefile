CXX      := g++
# -fno-inline: works around a MinGW-W64 inlining issue that causes segfaults
# at higher optimization levels with certain STL operations.
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -fno-inline -I include

SRCS := main.cpp \
        testing/ASGraph.cpp \
        testing/ASGraph_propagation.cpp \
        testing/stubs.cpp \
        testing/CSVIO.cpp

TARGET := bgp_sim

.PHONY: all clean parse_test

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Quick parser sanity check (separate binary in testing/)
parse_test:
	$(CXX) $(CXXFLAGS) -o testing/parse_test \
	    testing/parse_test.cpp \
	    testing/ASGraph.cpp \
	    testing/stubs.cpp \
	    testing/ASGraph_propagation.cpp \
	    testing/CSVIO.cpp

clean:
	rm -f $(TARGET) testing/parse_test
