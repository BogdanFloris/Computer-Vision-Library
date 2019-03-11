cmake_minimum_required(VERSION 3.13)
project(cv_library)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(cv_library
        src/args.c
        src/args.h
        src/image.h
        src/load_image.c
        src/process_image.c
        src/stb_image.h
        src/stb_image_write.h
        src/test.c
        src/test.h)
