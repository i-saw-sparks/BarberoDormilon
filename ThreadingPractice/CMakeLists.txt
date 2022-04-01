# CMakeList.txt: proyecto de CMake para ThreadingPractice, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.8)

# Agregue un origen al ejecutable de este proyecto.
add_executable (ThreadingPractice "ThreadingPractice.cpp" "ThreadingPractice.h" "Customer.cpp" "Customer.h" "WaitingSeat.cpp" "WaitingSeat.h" "Barber.cpp" "Barber.h")

# TODO: Agregue pruebas y destinos de instalación si es necesario.
