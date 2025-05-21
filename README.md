# 如何运行
> 本地缺什么自己 sudo apt-get install 就行（clang-format 需要这样手动装一下）（按照 Ubuntu 24 为例子）
## 1. 下载并安装 vcpkg
1. 克隆 `vcpkg` 仓库：
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg

2. 安装需要的依赖包：
vcpkg install --recurse abseil protobuf grpc redis-plus-plus gtest benchmark
> 如果遇到缺少某些依赖包，按照提示安装即可，重试命令。

## 2. 配置 vcpkg 和项目
1. 进入项目中的 `vcpkg` 文件夹。

2. 通过 `vcpkg.json` 配置文件自动安装所需依赖：
vcpkg install

## 3. 编译项目
1. 创建并进入 `build` 文件夹：
mkdir build
cd build

2. 使用 `CMake` 配置项目：
cmake .. -DCMAKE_TOOLCHAIN_FILE=/mnt/d/tools/vcpkg/scripts/buildsystems/vcpkg.cmake

3. 格式化代码（使用 `clang-format`）：
make format

4. 编译项目：
make

5. 执行编译后的程序：
./my_app

## 4. 发送 gRPC 请求（使用 Postman）

1. 获取 WSL2 网络接口 IP 地址：
ip addr show eth0 | grep inet

2. 在 Windows PowerShell 中测试连接：
Test-NetConnection -ComputerName <YOUR IP> -Port <YOUR PORT>

3. 在 Postman 中使用 gRPC 模式，同时导入 `.proto` 文件。
