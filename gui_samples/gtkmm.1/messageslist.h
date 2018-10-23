/*
 *  https://developer.gnome.org/gtkmm-tutorial/stable/chapter-introduction.html.en
 * 
 */

#ifndef GTKMM_EXAMPLE_MESSAGESLIST_H
#define GTKMM_EXAMPLE_MESSAGESLIST_H

#include <gtkmm.h>

class MessagesList: public Gtk::ScrolledWindow
{
public:
  MessagesList();
  virtual ~MessagesList();

  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:
    ModelColumns() { add(m_col_text); }

    Gtk::TreeModelColumn<Glib::ustring> m_col_text;
  };

  ModelColumns m_Columns;

protected:
  Glib::RefPtr<Gtk::ListStore> m_refListStore; //The Tree Model.
  Gtk::TreeView m_TreeView;                    //The Tree View.
};
#endif //GTKMM_EXAMPLE_MESSAGESLIST_H
