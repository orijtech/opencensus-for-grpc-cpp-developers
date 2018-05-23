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

#include <iostream>
#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>

#include "capitalize.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using capitalize::Fetch;
using capitalize::Payload;

class CapitalizeClient {
    public:
        CapitalizeClient(std::shared_ptr<Channel> channel) : stub_(Fetch::NewStub(channel)) {
        }

        std::string Capitalize(const std::string &str) {
            ClientContext context;
            Payload in;
            Payload *out = new Payload();
            in.set_data(str);
            this->stub_->Capitalize(&context, in, out);
            return out->data();
        }

    private:
        std::unique_ptr<Fetch::Stub> stub_;
};

int main() {
    CapitalizeClient client(
            grpc::CreateChannel("0.0.0.0:9988", grpc::InsecureChannelCredentials())
    );

    while (1) {
        std::cout << "\n> ";
        std::string input;
        std::getline(std::cin, input);
        const std::string res = client.Capitalize(input);
        std::cout << "< ";
        std::cout << res << std::endl;
    }
    return 0;
}
