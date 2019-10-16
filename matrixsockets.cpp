#include <string>
#include <sstream>
#include <iostream>
#include <list>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Infos.hpp>


std::stringstream buffer;


int main()
{
  curlpp::Easy myRequest;
  try
  {
    std::list<std::string> header;
    header.push_back("Content-Type: application/json");
    std::string body = "{ \"identifier\": { \"type\": \"m.id.user\", \"user\": \"USER\" }, \"initial_device_display_name\": \"Jungle Phone\", \"password\": \"PASSWORD\", \"type\": \"m.login.password\" }";
    curlpp::Cleanup myCleanup;

    myRequest.setOpt(curlpp::Options::Url("https://matrix.org/_matrix/client/unstable/login"));
    myRequest.setOpt(curlpp::Options::WriteStream(&buffer));
    myRequest.setOpt(curlpp::options::HttpHeader(header));
    myRequest.setOpt(curlpp::options::PostFields(body));
    myRequest.setOpt(curlpp::options::PostFieldSize(body.length()));

    myRequest.perform();
    std::cout << curlpp::Infos::ResponseCode::get(myRequest) << std::endl;
    std::cout << myRequest << std::endl;
  }
  catch (curlpp::RuntimeError &e)
  {
    std::cerr << e.what() << std::endl;
  }
  catch (curlpp::LogicError &e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
