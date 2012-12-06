include ../Makefile.inc

CFLAGS	= $(PRJCFLAGS)
OBJLIBS	= 
TARGETS = ./yamlParser.cpp
LIBS = -lSDL -lSDL_image -lyaml-cpp
EXTERNOBJ =  $(filter-out $(TARGETS), $(foreach path, ., $(wildcard $(path)/*.cpp)))
OBJS = $(EXTERNOBJ:.cpp=.o)

all: main
 
$(MAIN_DIR)/bin/%.o: %.cpp
#	$(ECHO) $(CC) $(CFLAGS) -o $@ $(LIBS)
	$(CC) -c $(CFLAGS) $(INCLUDES) $<
	

main: $(OBJS)

clean:
	rm -f *.o	

