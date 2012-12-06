include ../Makefile.inc

CFLAGS	= -Wall -pedantic -g -ggdb
OBJLIBS	= 
TARGETS = 
LIBS = -pthread
EXTERNOBJ =  $(filter-out $(TARGETS), $(foreach path, ., $(wildcard $(path)/*.cpp)))
OBJS = $(EXTERNOBJ:.cpp=.o)

all: main
 
$(MAIN_DIR)/bin/%.o: %.cpp
	$(ECHO) $(CC) $(CFLAGS) -o $@ $(LIBS)
	$(CC) -c $(CFLAGS) $(INCLUDES) $<
	

main: $(OBJS)

clean:
	rm -f *.o

