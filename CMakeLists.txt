cmake_minimum_required(VERSION 3.5)
project(corkus)

set(CMAKE_CXX_STANDARD 23)

add_executable(corkus Code/src/main.cpp
		Code/src/config.cpp
		Code/headers/config.h
		Code/src/quickmenu.cpp
		Code/headers/quickmenu.h
		Code/headers/main.h
		Code/src/main.cpp
		Code/src/options.cpp
		Code/headers/options.h
		Code/src/audit.cpp
		Code/headers/audit.h
		Code/headers/xmltemplates.h
		Code/src/xmltemplates.cpp
		Code/src/corkml.cpp
		Code/headers/corkml.h
		Code/src/path.cpp
		Code/headers/path.h
)

target_compile_options(corkus PRIVATE -Wall -Werror)
