#pragma once
#include <string>

class Contact
{
  public:
    Contact(std::string displayName,std::string userName);
    void setDisplayName(std::string displayName);
    void setUserName(std::string userName);
    std::string getDisplayName();
    std::string getUserName();

  private:
      std::string _displayName;
      std::string _userName;
};
