# opencensus-for-grpc-cpp-developers
OpenCensus for C++ developers

## Getting started
This tutorial assumes that you already know how to setup gRPC for C++.
If not, please see https://grpc.io/docs/tutorials/basic/c.html

### Generating code
Run `make`

### Running the code
In one terminal, run the server
```shell
$ ./capitalize_server 
Server listening on 0.0.0.0:9988
```

In another run the client
```shell
$ ./capitalize_client 

> foo
< FOO

> 😂 foo
< 😂 FOO

> boxing
< BOXING
```
