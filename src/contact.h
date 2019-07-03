#pragma once
#include <string>
#include <gnui/TextDisplay.h>


class Contact
{
  public:
    Contact(const std::string &dn,const std::string &un);
    void displayName(const std::string &dn);
    std::string displayName();
    void userName(const std::string &un);
    std::string userName();
    gnui::TextBuffer *buffer;

  private:
    std::string _displayName;
    std::string _userName;
};
