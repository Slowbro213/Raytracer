linkTarget = SempTracer

LIBS = -lSDL2


CFLAGS = -std=c++17


objects = main.o \
					CApp.o \
					$(patsubst %.cpp,%.o,$(wildcard tracer/*.cpp)) \
					$(patsubst %.cpp,%.o,$(wildcard tracer/Primitives/*.cpp)) \
					$(patsubst %.cpp,%.o,$(wildcard tracer/Lights/*.cpp)) \
					$(patsubst %.cpp,%.o,$(wildcard tracer/Materials/*.cpp)) \
					$(patsubst %.cpp,%.o,$(wildcard tracer/Textures/*.cpp)) \


rebuildables = $(objects) $(linkTarget)


$(linkTarget): $(objects)
	g++ -o $(linkTarget) $(objects) $(LIBS) $(CFLAGS)

%.o: %.cpp
	g++ -c $< -o $@ $(CFLAGS)

.PHONY:
clean:
	rm -f $(rebuildables) 

.PHONY:
unprofile:
	find . -name "*.gcda" -delete;
.PHONY:
fast:
	$(MAKE) $(linkTarget) CFLAGS="-Ofast -march=native -std=c++17"

.PHONY:
profile:
	$(MAKE) $(linkTarget) CFLAGS="-O3 -march=native -std=c++17 -fprofile-generate"

.PHONY:
profile-use:
	$(MAKE) $(linkTarget) CFLAGS="-O3 -march=native -std=c++17 -fprofile-use"
