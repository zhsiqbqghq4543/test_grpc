find_program(CLANG_FORMAT_EXE NAMES "clang-format" "clang-format-15" "clang-format-16" "clang-format-17" "clang-format-18")

if(CLANG_FORMAT_EXE)
    message(STATUS "clang-format found: ${CLANG_FORMAT_EXE}")
    
    # 获取所有源文件
    file(GLOB_RECURSE ALL_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    )
    
    # 创建格式化目标
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE} -style=file -i ${ALL_SOURCE_FILES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Formatting all source files with clang-format..."
    )
else()
    message(WARNING "clang-format not found! Formatting target will not be available.")
endif()