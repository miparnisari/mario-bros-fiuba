include ../Makefile.inc

CFLAGS	= $(PRJCFLAGS)
OBJLIBS	= 
TARGETS =
LIBS = 
EXTERNOBJ =  $(filter-out $(TARGETS), $(foreach path, ., $(wildcard $(path)/*.cpp)))
OBJS = $(EXTERNOBJ:.cpp=.o)

all: main
 
$(MAIN_DIR)/bin/%.o: %.cpp
#	$(ECHO) $(CC) $(CFLAGS) -o $@ $(LIBS)
	$(CC) -c $(CFLAGS) $(INCLUDES) $<
	

main: $(OBJS)


clean:
	rm -f *.o
#	rm modelo/main;
#	$(foreach path, $(EXTERN), rm $(wildcard $(path)/*.o))
