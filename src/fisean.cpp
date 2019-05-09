#include <gnui/run.h>
#include <gnui/Dial.h>
#include <gnui/Slider.h>
#include <gnui/Window.h>
#include <gnui/Group.h>
#include <gnui/Input.h>
#include <gnui/Button.h>
#include <gnui/TextDisplay.h>
#include <gnui/Browser.h>
#include <gnui/Item.h>
#include <gnui/events.h>
#include <arpa/inet.h>
#include <string>


class Params
{
  public:
    Params(gnui::TextBuffer *buff) { buffer = buff; }

    gnui::TextBuffer *buffer;
};


gnui::Browser *bro = nullptr;
gnui::TextDisplay *chat = nullptr;
gnui::Input *input = nullptr;
gnui::Button *button = nullptr;


void selectGroup(gnui::Widget *, void*)
{
  auto line = bro->value();
  if (line != -1)
  {
    gnui::Item *i = (gnui::Item *)bro->child(line);
    Params *p = (Params *)i->user_data();
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
    Params *p = (Params *)i->user_data();
    p->buffer->append(input->value());
    p->buffer->append("\n");
    input->value("");
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
    gnui::Group *grpInput = new gnui::Group(170,410,620,30);
    grpInput->begin();
    {
      input = new gnui::Input(0, 0, 550, 30);
      button = new gnui::Button(560, 0, 60, 30, "Send");
      grpInput->resizable(input);
    }
    grpInput->end();
    input->take_focus();

    gnui::TextBuffer *buff = new gnui::TextBuffer();
    buff->append("Mekanix: cao\n");
    buff->append("Momo: oj\n");
    Params *p = new Params(buff);
    bro->add("Meka", p);
    button->callback(sendMessage, p);
    button->shortcut(gnui::ReturnKey);

    buff = new gnui::TextBuffer();
    chat->buffer(*buff);
    p = new Params(buff);
    bro->add("Dervish", p);
    bro->callback(selectGroup);
    bro->select(1);
    window->resizable(chat);
  }
  window->end();
  window->show(argc, argv);
  return gnui::run();
}
