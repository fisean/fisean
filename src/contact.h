#pragma once
#include <string>

class Contact
{
  public:
    Contact(const std::string &dn,const std::string &un);
    void displayName(const std::string &displayName);
    std::string displayName();
    void userName(const std::string &userName);
    std::string userName();

  private:
      std::string _displayName;
      std::string _userName;
};
