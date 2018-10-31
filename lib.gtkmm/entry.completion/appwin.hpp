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
    app_win(void);
    virtual ~app_win(void);

  protected:
    void on_button_close();
    void on_select_action(int index);
    void init_completeion_list(void);

    //See the comment in the implementation:
    //bool on_completion_match(const Glib::ustring& key,
    //        const Gtk::TreeModel::const_iterator& iter);

    class tree_rec : public Gtk::TreeModel::ColumnRecord
    {
    public:
      tree_rec(void)
      {
        add(col_id);
        add(col_text);
      }
      virtual ~tree_rec(void);

      Gtk::TreeModelColumn<unsigned int> col_id {};
      Gtk::TreeModelColumn<Glib::ustring> col_text {};
    };

    tree_rec TreeMRecs {};

    std::map<int, Glib::ustring> mActions {};

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

