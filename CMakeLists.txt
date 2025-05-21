cmake_minimum_required(VERSION 3.15)
project(test_grpc)

include(cmake/Format.cmake)

# 1. 设置vcpkg工具链
set(CMAKE_TOOLCHAIN_FILE "/mnt/d/tools/vcpkg/scripts/buildsystems/vcpkg.cmake")

# 2. 查找依赖包
find_package(absl REQUIRED)
find_package(gRPC REQUIRED CONFIG)
find_package(Protobuf REQUIRED)

# 3. 查找工具
find_program(PROTOC protoc REQUIRED)
find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin REQUIRED)

# 4. 设置proto文件路径（关键修改）
set(PROTO_FILE "${CMAKE_CURRENT_SOURCE_DIR}/proto/test.proto")

# 5. 手动生成命令（替代protobuf_generate）
set(PROTO_SRCS "${CMAKE_CURRENT_BINARY_DIR}/test.pb.cc")
set(PROTO_HDRS "${CMAKE_CURRENT_BINARY_DIR}/test.pb.h")
set(GRPC_SRCS "${CMAKE_CURRENT_BINARY_DIR}/test.grpc.pb.cc")
set(GRPC_HDRS "${CMAKE_CURRENT_BINARY_DIR}/test.grpc.pb.h")

add_custom_command(
    OUTPUT ${PROTO_SRCS} ${PROTO_HDRS} ${GRPC_SRCS} ${GRPC_HDRS}
    COMMAND ${PROTOC}
    ARGS --grpc_out=${CMAKE_CURRENT_BINARY_DIR}
         --cpp_out=${CMAKE_CURRENT_BINARY_DIR}
         --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN}
         -I${CMAKE_CURRENT_SOURCE_DIR}/proto
         ${PROTO_FILE}
    DEPENDS ${PROTO_FILE}
    COMMENT "Generating gRPC code for ${PROTO_FILE}"
    VERBATIM
)

# 6. 创建可执行文件
add_executable(grpc_server
    src/main.cpp
    src/rpc_service.h
    ${PROTO_SRCS}
    ${PROTO_HDRS}
    ${GRPC_SRCS}
    ${GRPC_HDRS}
)

# 7. 包含目录
target_include_directories(grpc_server PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/proto
)

# 8. 链接库
target_link_libraries(grpc_server PRIVATE
    absl::strings
    absl::status
    absl::statusor
    gRPC::grpc++
    gRPC::grpc
    gRPC::grpc++_reflection
    ${PROTOBUF_LIBRARIES}
)

# 9. 设置C++标准
set_target_properties(grpc_server PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

message(STATUS "----------------------------------------")
message(STATUS "Build configuration successful!")
message(STATUS "Proto file: ${PROTO_FILE}")
message(STATUS "Protoc: ${PROTOC}")
message(STATUS "gRPC plugin: ${GRPC_CPP_PLUGIN}")
message(STATUS "Generated files will be in: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "----------------------------------------")