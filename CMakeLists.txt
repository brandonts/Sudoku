cmake_minimum_required( VERSION 3.0 )

project( sudoku_solver)

#aux_source_directory(. SRC_LIST)
#set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(ss ./basic_sudoku_solver.cpp ./ncurses_sudoku_solver.cpp ./wxwidgets_sudoku_solver.cpp ./main_sudoku_solver.cpp ./sudoku_logic_stack.cpp ./Sudoku_Puzzle/sudoku_puzzle.cpp )

target_link_libraries(ss ${wxWidgets_LIBRARIES})
target_link_libraries(ss ${CURSES_LIBRARY})

