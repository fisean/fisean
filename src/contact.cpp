#include "contact.h"
#include <string>

Contact::Contact(const std::string &dn,const std::string &un)
{
  displayName(dn);
  userName(un);
}
void Contact::displayName(const std::string &dn)
{
  _displayName=dn;
}
void Contact::userName(const std::string &un)
{
  _userName=un;
}
std::string Contact::displayName()
{
  return _displayName;
}
std::string Contact::userName()
{
  return _userName;
}
