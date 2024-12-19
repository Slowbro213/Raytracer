linkTarget = SempTracer

LIBS = -lSDL2


CFLAGS = -std=c++17


objects = main.o \
					CApp.o \
					$(patsubst %.cpp,%.o,$(wildcard tracer/*.cpp)) \


rebuildables = $(objects) $(linkTarget)


$(linkTarget): $(objects)
	g++ -o $(linkTarget) $(objects) $(LIBS) $(CFLAGS)

%.o: %.cpp
	g++ -c $< -o $@ $(CFLAGS)

.PHONY:
clean:
	rm -f $(rebuildables) 

.PHONY:
fast:
	$(MAKE) $(linkTarget) CFLAGS="-Ofast -march=native -funroll-loops -std=c++17"

