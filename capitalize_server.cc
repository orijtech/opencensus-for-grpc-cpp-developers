// Copyright 2018, OpenCensus Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>

#include "capitalize.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::Status;
using capitalize::Fetch;
using capitalize::Payload;

class CapitalizeImpl final : public Fetch::Service {
    public:
        explicit CapitalizeImpl(const std::string& init) {
        }

        Status Capitalize(ServerContext *context, const Payload  *req, Payload *res) override {
            std::string inStr = req->data();
            std::string out(inStr);
            for (auto it = out.begin(); it != out.end(); it++) {
                *it = std::toupper(*it);
            }
            res->set_data(out);
            return Status::OK;
        }
};

void runServer(const std::string& addr) {
    CapitalizeImpl service("");

    ServerBuilder builder;
    builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << addr << std::endl;
    server->Wait();
}

int main(int argc, char **argv) {
    runServer("0.0.0.0:9988");
    return 0;
}
