# Chess
This is a Chess application implemented in C++ using wxWidgets. The program allows you to play a game of Chess, following all the standard rules of Chess, and it also checks for draws and checkmates. It provides a graphical user interface (GUI) to facilitate an intuitive gameplay experience.

## Features
- Visualize all the legal moves for the piece the user clicks
- Check for draws and checkmates to determine the games outcome
- Convenient GUI for easy interaction with the pieces

## Build Instructions
1. Clone the repository to your machine.
```bash
git clone https://github.com/jpope6/chess-v2.git
cd chess-v2
```
2. Create a build directory and navigate to it
```bash
mkdir build
cd build
```
3. Generate build files using CMAKE
```bash
cmake ..
```
4. Build the application
```bash
make
```
5. Return to the root directory
```bash
cd ..
```
6. Run the application
```
./main
```

## Future plans
- Create a bot for the user to play against

## License
This application is available under the MIT License
