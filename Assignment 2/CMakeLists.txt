project(A2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

foreach(X IN ITEMS 1 2 3 4 5 6)
    add_executable("A2_${X}" "${A2_SOURCE_DIR}/${X}.cpp"
            bartlett.h)
endforeach()
