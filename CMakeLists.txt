
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
cmake_minimum_required(VERSION 3.12)
project(Chess)

set(CMAKE_CXX_STANDARD 11)

# Include the wxWidgets package
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# Add all the source files to a variable
set(SOURCES
    frame/frame.cpp
    board/board.cpp
    pieces/piece.cpp
    pieces/pawn/pawn.cpp
    pieces/rook/rook.cpp
    pieces/bishop/bishop.cpp
    pieces/knight/knight.cpp
    pieces/queen/queen.cpp
    pieces/king/king.cpp
    main.cpp
)

# Create the executable and link it with wxWidgets libraries
add_executable(main ${SOURCES})
target_link_libraries(main PRIVATE ${wxWidgets_LIBRARIES})

