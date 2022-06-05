cmake_minimum_required(VERSION 3.20)
project(SO C)

set(CMAKE_C_STANDARD 99)

add_executable(SO "main.c" "Parte 1/process.c" "Parte 1/process.h" "Parte 1/pipes.c" "Parte 1/pipes.h" "Parte 1/pipes_2_.c" "Parte 1/pipes_2_.h" "Parte 2/threads.c" "Parte 2/threads.h" "Parte 2/Produtor_Consumidor.c" "Parte 2/Produtor_Consumidor.h" "Parte 2/Produtor_Consumidor_2_.c" "Parte 2/Produtor_Consumidor_2_.h")
