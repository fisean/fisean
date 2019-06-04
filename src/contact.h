#pragma once
#include <string>

typedef class contact
{
  public:
    contact(std::string displayName,std::string userName);
    void setDisplayName(std::string displayName);
    void setUserName(std::string userName);
    std::string getDisplayName();
    std::string getUserName();

  private:
      std::string _displayName="";
      std::string _userName="";
}contact;
