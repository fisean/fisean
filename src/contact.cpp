#include "contact.h"
#include <string>
    contact::contact(std::string displayName,std::string userName)
    {
      this->setDisplayName(displayName);
      this->setUserName(userName);
    }
    void contact::setDisplayName(std::string displayName)
    {
      _displayName=displayName;
    }
    void contact::setUserName(std::string userName)
    {
      _userName=userName;
    }
    std::string contact::getDisplayName()
    {
      return _displayName;
    }
    std::string contact::getUserName()
    {
      return _userName;
    }

