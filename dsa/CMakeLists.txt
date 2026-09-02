# Every subfolder gets its own build target + its own registered test,
# without you hand-writing a rule per problem.
file(GLOB PROBLEM_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */)

foreach(dir ${PROBLEM_DIRS})
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/solution.cpp)
        add_executable(${dir} ${dir}/solution.cpp)
        add_test(NAME ${dir} COMMAND ${dir})
    endif()
endforeach()
