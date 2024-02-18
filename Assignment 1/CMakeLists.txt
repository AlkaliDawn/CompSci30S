project(A1)

foreach(X IN ITEMS 1 2 3 4 5 6)
    add_executable("${X}" "${A1_SOURCE_DIR}/${X}.cpp")
endforeach()
