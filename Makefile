args = -O0
libs = -l ncursesw

sources := $(shell find src -name "*.cpp")
objects := $(patsubst %.cpp,out/%.o, $(notdir $(sources)))

all: $(objects) | out
	g++ $(objects) -o out/main $(libs)
	./out/main

out/%.o: src/%.cpp | out
	g++ -c $< -o $@ $(args) $(libs)

out:
	mkdir -p out