#!/bin/bash

echo "Compiling frame.cpp"
g++ -c frame/frame.cpp `wx-config --cxxflags --libs`

echo "Compiling board.cpp"
g++ -c board/board.cpp `wx-config --cxxflags --libs`

echo "Compiling piece.cpp"
g++ -c pieces/piece.cpp `wx-config --cxxflags --libs`

echo "Compiling pawn.cpp"
g++ -c pieces/pawn/pawn.cpp `wx-config --cxxflags --libs`

echo "Compiling rook.cpp"
g++ -c pieces/rook/rook.cpp `wx-config --cxxflags --libs`

echo "Compiling bishop.cpp"
g++ -c pieces/bishop/bishop.cpp `wx-config --cxxflags --libs`

echo "Compiling knight.cpp"
g++ -c pieces/knight/knight.cpp `wx-config --cxxflags --libs`

echo "Compiling queen.cpp"
g++ -c pieces/queen/queen.cpp `wx-config --cxxflags --libs`

echo "Compiling king.cpp"
g++ -c pieces/king/king.cpp `wx-config --cxxflags --libs`

echo "Compiling main.cpp"
g++ -c main.cpp `wx-config --cxxflags --libs`

echo "Linking main.o"
g++ -o main main.o frame.o board.o piece.o pawn.o rook.o bishop.o knight.o queen.o king.o `wx-config --cxxflags --libs`

echo "Running main.o"
./main

echo "Execution completed successfully."

echo "Removing object files"
rm *.o
