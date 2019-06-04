#include "contact.h"
#include <string>
    Contact::Contact(std::string displayName,std::string userName)
    {
      this->setDisplayName(displayName);
      this->setUserName(userName);
    }
    void Contact::setDisplayName(std::string displayName)
    {
      _displayName=displayName;
    }
    void Contact::setUserName(std::string userName)
    {
      _userName=userName;
    }
    std::string Contact::getDisplayName()
    {
      return _displayName;
    }
    std::string Contact::getUserName()
    {
      return _userName;
    }

