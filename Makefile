
CFLAGS=-Wall -Werror -std=gnu99 -static -DTAGLIB_STATIC 
LDFLAGS=-L. -static-libgcc -static-libstdc++
LDLIBS=-lavisynth -ltag_c -ltag

all: id3.dll

test: test.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.dll : %.o
	$(CXX) $(LDFLAGS) -shared -o $@ $^ $(LDLIBS)


