
#include "HelloWorldClient.h"
#include "HelloWorldClient_impl.h"

#include <memory>


using std::unique_ptr;

namespace hello_world {

unique_ptr<HelloWorldClient> HelloWorldClient::CreateInstance() {

  auto hello_world_client_impl = new internal::DBusHelloWorldClient{};
  auto ret = unique_ptr<HelloWorldClient>{hello_world_client_impl};

  if (!hello_world_client_impl->Init()) {
      ret.reset();
  }

  return ret;
}


}  // namespace hello_world