#!/bin/bash

echo "Compiling main.cpp"
g++ -o main main.cpp frame/frame.cpp board/board.cpp `wx-config --cxxflags --libs`

echo "Running main.cpp"
./main

echo "Execution completed successfully."
rm main
