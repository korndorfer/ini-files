all: ini-files

CC       = g++
SRCDIR   = src
WARNINGS = -Wall
DEBUG    = -ggdb -fno-omit-frame-pointer
OPTIMIZE = -O2
DEPSRCS  = $(wildcard $(SRCDIR)/*.h)
SOURCES  = $(wildcard $(SRCDIR)/*.cpp)
PROGRAM  = ini-files

%.o: %.cpp $(DEPSRCS)
	$(CC) -c -o $@ $(WARNINGS) $(DEBUG) $(OPTIMIZE)

$(PROGRAM): Makefile $(SOURCES)
	$(CC) -o $@ $(WARNINGS) $(DEBUG) $(OPTIMIZE) $(SOURCES)

clean:
	rm -f $(PROGRAM) tags.* $(SRCDIR)/tags.*

install:
	echo "Installing is not supported (yet)."

run:
	./$(PROGRAM)
