CXX = g++
CXXFLAGS = -O2 -Wall -Wextra
LD = g++
LDFLAGS = -s -static

OBJS = \
	zahyou-tateru.o \
	point-corner.o \
	plaintext.o \
	stltext.o

zahyou-tateru: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

.PHONY: clean
clean:
	rm -rf $(OBJS)
