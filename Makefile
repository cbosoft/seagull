CXX ?= g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -O2

HDR = $(shell ls src/*.hpp)
OBJ = obj/main.o obj/cpu.o obj/gpu.o obj/runsh.o obj/legend.o obj/process.o obj/trim.o
LINK = -lplot -lcurses
DEFS =
INSTALL_PREFIX = /usr/local

## Colours
COL_OBJ = $(shell tput setaf 3 2>/dev/null)
COL_EXE = $(shell tput setaf 4 2>/dev/null)
COL_RST = $(shell tput sgr0 2>/dev/null)
COL_BLD = $(shell tput bold 2>/dev/null)

.SECONDARY:

obj/%.o: src/%.cpp $(HDR)
	@printf "$(COL_OBJ)ASSEMBLING OBJECT $@$(COL_RST)\n"
	@mkdir -p `dirname $@`
	@$(CXX) $(CFLAGS) $(DEFS) $< -c -o $@

.PHONY: all options

all: options seagull libplot.so

options:
	@printf "Compiler: $(COL_BLD)$(CXX)$(COL_RST)\n"

seagull: $(OBJ) $(HDR)
	@printf "$(COL_OBJ)LINKING OBJECTS TO EXECUTABLE $@$(COL_RST)\n"
	@$(CXX) $(CFLAGS) $(DEFS) $(OBJ) -o $@ $(LINK)

libplot.so:
	cd plot && meson build && ninja -C build
	cp plot/build/lib/libplot.so .

install: seagull libplot.so
	cp seagull $(INSTALL_PREFIX)/bin/seagull
	cp libplot.so $(INSTALL_PREFIX)/lib/libplot.so

uninstall:
	rm $(INSTALL_PREFIX)/bin/seagull

clean:
	rm -rf obj seagull libplot.so
