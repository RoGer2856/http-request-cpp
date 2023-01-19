#!/bin/bash

mkdir build
cd build

conan install ../ --build
cmake ../
make
