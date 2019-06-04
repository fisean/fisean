#include "contact.h"
#include <string>

Contact::Contact(const std::string &dn,const std::string &un)
{
  displayName(dn);
  userName(un);
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
