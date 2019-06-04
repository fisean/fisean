#include "contact.h"
#include <string>

Contact::Contact(std::string displayName,std::string userName)
{
  this->displayName(displayName);
  this->userName(userName);
}
void Contact::displayName(const std::string &displayName)
{
  _displayName=displayName;
}
void Contact::userName(const std::string &userName)
{
  _userName=userName;
}
std::string Contact::displayName()
{
  return _displayName;
}
std::string Contact::userName()
{
  return _userName;
}
