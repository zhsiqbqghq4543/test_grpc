#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include <memory>
#include <string>

#include "rpc_service.h"
#include "test.grpc.pb.h"
#include "test.pb.h"

namespace {

constexpr char kServerAddress[] = "0.0.0.0:50051";

}  // namespace

int main(int argc, char** argv) {
  // 1. 创建服务实例
  TestEcho service;

  // 2. 构建 gRPC 服务器
  grpc::EnableDefaultHealthCheckService(true);
  grpc::ServerBuilder builder;

  // 3. 监听端口（非加密）
  builder.AddListeningPort(kServerAddress, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  // 4. 启动服务器
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  if (server == nullptr) {
    std::cerr << "Failed to start server on " << kServerAddress << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Server listening on " << kServerAddress << std::endl;

  // 5. 保持运行直到终止
  server->Wait();
  return EXIT_SUCCESS;
}