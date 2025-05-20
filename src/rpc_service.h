#ifndef RPC_SERVICE_H_
#define RPC_SERVICE_H_

#include <string>
#include <stdexcept>  // 添加标准异常头文件

#include <absl/strings/str_cat.h>

#include "test.pb.h"
#include "test.grpc.pb.h"

class TestEcho final : public test::TestService::Service {
public:
    grpc::Status Echo(grpc::ServerContext* context,
                     const test::TestRequest* request,
                     test::TestResponse* response) override {
        const std::string& req_str = request->req_str();
        
        try {
            response->set_res_str(absl::StrCat("RPC REQ:", req_str));
        } catch (const std::exception& e) {  // 修改为标准的std::exception
            return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
        }
        
        return grpc::Status::OK;
    }
};

#endif  // RPC_SERVICE_H_