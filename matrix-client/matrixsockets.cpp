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
  cURLpp::Easy myRequest;
  try
  {
    std::list<std::string> header;
    header.push_back("Content-Type: application/json");
    std::string body = "{ \"identifier\": { \"type\": \"m.id.user\", \"user\": \"USER\" }, \"initial_device_display_name\": \"Jungle Phone\", \"password\": \"PASSWORD\", \"type\": \"m.login.password\" }";
    cURLpp::Cleanup myCleanup;

    myRequest.setOpt(cURLpp::Options::Url("https://matrix.org/_matrix/client/unstable/login"));
    myRequest.setOpt(cURLpp::Options::WriteStream(&buffer));
    myRequest.setOpt(cURLpp::options::HttpHeader(header));
    myRequest.setOpt(cURLpp::options::PostFields(body));
    myRequest.setOpt(cURLpp::options::PostFieldSize(body.length()));

    myRequest.perform();
    std::cout << cURLpp::Infos::ResponseCode::get(myRequest) << std::endl;
    std::cout << myRequest << std::endl;
  }
  catch (cURLpp::RuntimeError &e)
  {
    std::cout << e.what() << std::endl;
  }
  catch (cURLpp::LogicError &e)
  {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
