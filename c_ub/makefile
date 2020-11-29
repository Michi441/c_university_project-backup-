CFLAGS=-MMD -MP -Wall

PROGRAMS=programm
OBJECTS=program.o stadt.o region.o

ALLOBJECTS=$(OBJECTS) $(patsubst %,%.o,$(PROGRAMS))

default: $(PROGRAMS)

program: $(OBJECTS)

clean:
	-rm -f $(ALLOBJECTS) $(ALLOBJECTS:%.o=%.d) $(PROGRAMS)

-include $(ALLOBJECTS:%.o=%.d)
