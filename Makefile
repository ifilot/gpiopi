# set compiler and compile options
EXEC = gpio-pi
CXX = g++                                # use the GNU C++ compiler
OPTS = -O0 -Wall -std=c++0x -Wno-write-strings  # use some optimization, report all warnings and enable debugging
CFLAGS = $(OPTS)                         # add compile flags
LDFLAGS =                                # specify link flags here

# set a list of directories
OBJDIR = ./obj
BINDIR = ./bin
SRCDIR = ./src

# set the include folder where the .h files reside
CFLAGS += -I$(SRCDIR)

# add here the source files for the compilation
SOURCES = main.cpp gpio.cpp rpicsb.cpp

# create the obj variable by substituting the extension of the sources
# and adding a path
_OBJ = $(SOURCES:.cpp=.o)
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

all: $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC): $(OBJ)
	$(CXX) -o $(BINDIR)/$(EXEC) $(OBJ) $(LDFLAGS) && sudo chown 0:0 $(BINDIR)/$(EXEC) && sudo chmod u+s $(BINDIR)/$(EXEC)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c -o $@ $< $(CFLAGS)

test: $(BINDIR)/$(EXEC)
	$(BINDIR)/$(EXEC)

clean:
	rm -vf $(BINDIR)/$(EXEC) $(OBJ)
