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
#include <gnui/MenuBar.h>
#include <gnui/ItemGroup.h>
#include <gnui/Item.h>
#include <gnui/TabGroup.h>
#include <gnui/CheckButton.h>
#include <gnui/FileBrowser.h>
#include <gnui/RadioButton.h>
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


void cb_Close(gnui::Widget *item, void *data)
{
  auto w = (gnui::Window *)data;
  w->hide();
  delete w;
}

void cb_Preferences(gnui::Item*, void*) {
  gnui::Window* w;
   {
    w = new gnui::Window(700, 490, "Preferences");
    w->shortcut(0xff1b);
    w->begin();
     {gnui::TabGroup* w = new gnui::TabGroup(0, 0, 700, 440);
      w->begin();
       {gnui::Group* w = new gnui::Group(0, 25, 700, 415, "General");
        w->begin();
        new gnui::CheckButton(25, 25, 25, 25, "Start minimized");
        new gnui::CheckButton(25, 50, 25, 25, "Start on boot/login");
        new gnui::CheckButton(25, 75, 25, 25, "Minimize on close");
        new gnui::CheckButton(25, 100, 25, 25, "Confirm exit");
        new gnui::CheckButton(400, 25, 25, 25, "Logging");
         {gnui::Group* w = new gnui::Group(420, 50, 215, 50);
          w->deactivate();
          w->begin();
          new gnui::FileBrowser(0, 0, 70, 25);
          new gnui::Button(70, 0, 60, 25, "Browse");
          w->end();
        }
        w->end();
      }
       {gnui::Group* w = new gnui::Group(0, 25, 700, 415, "Notifications");
        w->hide();
        w->begin();
        new gnui::CheckButton(25, 25, 25, 25, "Enable notifications");
         {gnui::Group* w = new gnui::Group(50, 50, 100, 100);
          w->set_vertical();
          w->deactivate();
          w->begin();
          new gnui::CheckButton(0, 0, 25, 25, "Sound");
          new gnui::CheckButton(0, 50, 25, 25, "Popup");
          w->end();
        }
         {gnui::Group* w = new gnui::Group(75, 75, 165, 25);
          w->deactivate();
          w->begin();
          new gnui::FileBrowser(0, 0, 100, 25);
          new gnui::Button(105, 0, 60, 25, "Browse");
          w->end();
        }
        w->end();
      }
       {gnui::Group* w = new gnui::Group(0, 25, 700, 415, "Encription");
        w->hide();
        w->begin();
        new gnui::CheckButton(25, 25, 25, 25, "Enable OMEMO encription");
         {gnui::Group* w = new gnui::Group(50, 50, 100, 100);
          w->set_vertical();
          w->deactivate();
          w->begin();
          new gnui::RadioButton(0, 0, 25, 25, "Always");
          new gnui::RadioButton(0, 25, 25, 25, "Ask");
          w->end();
        }
        w->end();
      }
      w->end();
    }
    new gnui::Button(25, 450, 110, 25, "Restore defaults");
    new gnui::Button(450, 450, 110, 25, "Ok");
    gnui::Button *b = new gnui::Button(565, 450, 110, 25, "Cancel");
    b->callback(cb_Close, w);
    w->end();
    w->resizable(w);
  }
  w->show();

}

void cb_PreferencesBackup(gnui::Item*, void*) {
  gnui::Window* w;
   {
    w = new gnui::Window(230, 125, "Preferences");
    w->shortcut(0xff1b);
    w->begin();
    {
      gnui::Button *b = new gnui::Button(45, 28, 131, 57, "Close");
      b->callback(cb_Close, w);
    }
    w->end();
    w->set_modal();
    w->resizable(w);
  }
  w->show();

}

void cb_About(gnui::Widget*, void *) {
  gnui::Window* w;
   {
    w = new gnui::Window(230, 125, "About");
    w->shortcut(0xff1b);
    w->begin();
    {
      gnui::Button *b = new gnui::Button(45, 28, 131, 57, "Close");
      b->callback(cb_Close, w);
    }
    w->end();
    w->set_modal();
    w->resizable(w);
  }
  w->show();
}


int main(int argc, char **argv)
{

  gnui::Window *window = new gnui::Window(800, 475);
  window->begin();
  {
    gnui::MenuBar* o = new gnui::MenuBar(0, 0, 230, 25);
    o->shortcut(0xffe9);
      o->begin();
       {gnui::ItemGroup* o = new gnui::ItemGroup("Edit");
        o->begin();
         {gnui::Item* o = new gnui::Item("Preferences");
          o->callback((gnui::Callback*)cb_Preferences);
        }
        o->end();
      }
       {gnui::ItemGroup* o = new gnui::ItemGroup("Help");
        o->begin();
         {gnui::Item* o = new gnui::Item("About");
          o->callback(cb_About);
        }
        o->end();
      }
      o->end();
    bro = new gnui::Browser(10, 35, 150, 430);
    chat = new gnui::TextDisplay(170, 35, 620, 390);
    gnui::Group *grpInput = new gnui::Group(170, 435, 620, 30);
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
