#!/bin/sh
echo "Compiling code..."
gcc -o main main.c pizza.c pizzaenc.c arvbm.c categoria.c
echo "Done."
