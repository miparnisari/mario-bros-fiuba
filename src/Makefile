include Makefile.inc

LIBS = -lSDL_gfx -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lyaml-cpp -pthread
DIRS	= comun movimientos server jugador modelo bonus controlador vista factories other eventos app 
TARGETS = main.cpp
EXTERNOBJ =  $(foreach path, $(DIRS), $(wildcard $(path)/*.o))
EXE	= main
OBJLIBS	= comun.a movimientos.a server.a jugador.a eventos.a modelo.a bonus.a controlador.a vista.a factories.a other.a app.a
I-SUBDIRS = $(addprefix -I, $(DIRS))
all : $(EXE)

main: $(OBJLIBS)
	find * -type d -exec mkdir -p ../bin/\{\} \; 
	$(ECHO)  $(CC) $(CFLAGS) $(I-SUBDIRS) -o $@ $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(EXTERNOBJ) $(I-SUBDIRS) -o $@ $(TARGETS)  $(LIBS)
#	-for d in $(DIRS); do (for f in $$d/*.o; do (mv ./$$f $(BIN_DIR)$$f); done);done
#	cp -r images $(BIN_DIR)
#	mv $@ $(BIN_DIR)$@




%.a:
	-for d in $(DIRS); do (cd $$d; $(MAKE)); done
	
clean :
	$(ECHO) Borrando archivos.
	-$(RM) -f ./main
	find . -name "*.o" -type f -print | xargs /bin/rm -f
	-$(RM) -f ./tmp/*.yaml
	-$(RM) -f ./tmp/images/*.png
