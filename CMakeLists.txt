cmake_minimum_required(VERSION 3.13)
project(cv_library C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(cv_library
        src/args.c
        src/args.h
        src/filter_image.c
        src/image.h
        src/load_image.c
        src/main.c
        src/process_image.c
        src/resize_image.c
        src/stb_image.h
        src/stb_image_write.h
        src/test.c
        src/test.h)
