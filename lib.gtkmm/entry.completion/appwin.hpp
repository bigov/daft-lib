/* Filename: appwin.hpp
 *
 */
#ifndef APPWIN_HPP
#define APPWIN_HPP

#include <iostream>
#include <gtkmm.h>

class app_win : public Gtk::Window
{
  public:
    app_win();
    ~app_win() {}

  protected:
    //signals
    void on_chexkbox_editable_toggled();
    void on_checkbox_visibility_toggled();
    void on_button_close();
    void on_completion_activated(int index);
    //See the comment in the implementation:
    //bool on_completion_match(const Glib::ustring& key,
    //        const Gtk::TreeModel::const_iterator& iter);

    class model_columns : public Gtk::TreeModel::ColumnRecord
    {
    public:
      model_columns(void)
      {
        add(m_col_id);
        add(m_col_name);
      }
      Gtk::TreeModelColumn<unsigned int> m_col_id {};
      Gtk::TreeModelColumn<Glib::ustring> m_col_name {};
    };

    model_columns TreeModColRecord {};

    typedef std::map<int, Glib::ustring> type_actions_map;
    type_actions_map mCompletionActions {};

    Gtk::Box mHBox { Gtk::ORIENTATION_HORIZONTAL };
    Gtk::Box mVBox { Gtk::ORIENTATION_VERTICAL };
    Gtk::Entry mEntry {};
    Gtk::Label mLabel {
      "Press a or b to see a list of possible completions and actions."};
    Gtk::CheckButton
      mCheckButtonEditable {"Editable"},
      mCheckButtonVisible {"Visible"};
    Gtk::Button mButtonClose {"Close"};
 };

#endif //APPWIN_HPP

