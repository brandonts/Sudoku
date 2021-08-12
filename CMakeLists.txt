cmake_minimum_required( VERSION 3.0 )

project( sudoku_solver)

aux_source_directory(. SRC_LIST)
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})
include(${wxWidgets_USE_FILE})

add_executable(ss ./basic_sudoku_solver.cpp ./ncurses_sudoku_solver.cpp ./wxwidgets_sudoku_solver.cpp ./main_sudoku_solver.cpp ./sudoku_logic_stack.cpp ./Sudoku_Puzzle/sudoku_puzzle.cpp )
target_link_libraries(ss ${wxWidgets_LIBRARIES})
target_link_libraries(ss ${CURSES_LIBRARY})
#target_compile_definitions(ss PUBLIC -lncurses `wx-config --libs --cxxflags` -Wall)
#target_include_directories(ss PUBLIC ./wx/gtk ./wx)
#3rd party libs

