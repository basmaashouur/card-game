# Games Library 

## About
This project is a c++ games box made witf SFML library.

## C++ libraries 
- SFML 2.4.2

## Pre-Requirements
- g++

## Setup for linux
- Installing SFML
```
sudo apt-get install libsfml-dev
```
- Download this Repo

## Compile and Run
- Go to the required game directory for example you wanna run cards game `cd GamesLib/cards`
- Compile the file `g++ -c main.cpp`
- Link the compiled file to the SFML libraries 
```
g++ main.o -o card-game -lsfml-graphics -lsfml-window -lsfml-system
```
- Execute the compiled program `/card-game`

