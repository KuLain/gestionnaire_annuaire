cmake_minimum_required(VERSION 3.20)
project(sae_1_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(sae_1_2 main.c
        header/struct/FixedString.h
        src/struct/FixedString.c
        header/struct/Record.h
        src/struct/Record.c
        header/struct/List.h
        src/struct/List.c
        )
