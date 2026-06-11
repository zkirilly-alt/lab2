default_target: all
.PHONY : default_target
.NOTPARALLEL:

.SUFFIXES:

% : %,v


% : RCS/%


% : RCS/%,v


% : SCCS/s.%


% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list


$(VERBOSE)MAKESILENT = -s


$(VERBOSE).SILENT:


cmake_force:
.PHONY : cmake_force


SHELL = /bin/sh


CMAKE_COMMAND = /usr/bin/cmake


RM = /usr/bin/cmake -E rm -f


EQUALS = =


CMAKE_SOURCE_DIR = /home/zx/Documents/progi/lab2


CMAKE_BINARY_DIR = /home/zx/Documents/progi/lab2/build





edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache


edit_cache/fast: edit_cache
.PHONY : edit_cache/fast


rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache


rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast


all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/zx/Documents/progi/lab2/build/CMakeFiles /home/zx/Documents/progi/lab2/build//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/zx/Documents/progi/lab2/build/CMakeFiles 0
.PHONY : all


clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean


clean/fast: clean
.PHONY : clean/fast


preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall


preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast


depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend





lab2_gtk: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 lab2_gtk
.PHONY : lab2_gtk


lab2_gtk/fast:
	$(MAKE) $(MAKESILENT) -f src/CMakeFiles/lab2_gtk.dir/build.make src/CMakeFiles/lab2_gtk.dir/build
.PHONY : lab2_gtk/fast


help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... lab2_gtk"
.PHONY : help









cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

