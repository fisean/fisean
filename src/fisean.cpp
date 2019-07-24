#include <arpa/inet.h>
#include <gnui/Browser.h>
#include <gnui/Button.h>
#include <gnui/Dial.h>
#include <gnui/Group.h>
#include <gnui/Input.h>
#include <gnui/Item.h>
#include <gnui/Slider.h>
#include <gnui/TextDisplay.h>
#include <gnui/Window.h>
#include <gnui/events.h>
#include <gnui/run.h>
#include <string>
#include <string.h>
#include <iostream>

#include <fisean/contact.h>


gnui::Browser *bro = nullptr;
gnui::TextDisplay *chat = nullptr;
gnui::Input *input = nullptr;
gnui::Button *button = nullptr;


void selectGroup(gnui::Widget *, void *)
{
  auto line = bro->value();
  if (line != -1)
  {
    gnui::Item *i = (gnui::Item *)bro->child(line);
    Contact *p = (Contact *)i->user_data();
    chat->buffer(p->buffer);
  }
  input->take_focus();
}


void sendMessage(gnui::Widget *, void *v)
{
  auto line = bro->value();
  if (line != -1)
  {
    gnui::Item *i = (gnui::Item *)bro->child(line);
    Contact *p = (Contact *)i->user_data();
    if (strlen(input->value()) != 0)
    {
      p->buffer->append(input->value());
      p->buffer->append("\n");
      input->value("");
    }
  }
  input->take_focus();
}


int main(int argc, char **argv)
{

  gnui::Window *window = new gnui::Window(800, 450);
  window->begin();
  {
    bro = new gnui::Browser(10, 10, 150, 430);
    chat = new gnui::TextDisplay(170, 10, 620, 390);
    gnui::Group *grpInput = new gnui::Group(170, 410, 620, 30);
    grpInput->begin();
    {
      input = new gnui::Input(0, 0, 550, 30);
      button = new gnui::Button(560, 0, 60, 30, "Send");
      grpInput->resizable(input);
    }
    grpInput->end();
    input->take_focus();

    Contact *meka = new Contact("Mekanix", "Goran");
    bro->add(meka->displayName().data(), meka);

    Contact *dervish = new Contact ("Dervish", "Rajko");
    bro->add(dervish->displayName().data(), dervish);

    bro->callback(selectGroup);
    bro->select(1);
    chat->buffer(dervish->buffer);
    button->callback(sendMessage);
    button->shortcut(gnui::ReturnKey);
    window->resizable(chat);
  }
  window->end();
  window->show(argc, argv);
  return gnui::run();
}
