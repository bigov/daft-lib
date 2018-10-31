/* Filename: appwin.cpp
 *
 */
#include "appwin.hpp"

///
/// \brief app_win::app_win
///
app_win::app_win(void)
{
  set_size_request(200, 200);
  set_title("EntryCompletion demo");
  set_border_width(8);

  add(mVBox);

  mVBox.pack_start(mEntry, Gtk::PACK_SHRINK);
  mVBox.pack_start(mLabel, Gtk::PACK_EXPAND_WIDGET);
  mVBox.pack_start(mButtonClose, Gtk::PACK_SHRINK);

  mEntry.set_max_length(50);
  mEntry.set_text("Hello");

  mButtonClose.signal_clicked().connect(
    sigc::mem_fun(*this, &app_win::on_button_close));
  mButtonClose.set_can_default();
  mButtonClose.grab_default();

  init_completeion_list();
  show_all_children();
  return;
}

///
/// \brief app_win::init_completeion_list
///
void app_win::init_completeion_list(void)
{
  auto LSRows = Gtk::ListStore::create(TreeMRecs);
  auto EntryComplet = Gtk::EntryCompletion::create();
  EntryComplet->set_model(LSRows);
  //display text in the entry when a match is found.
  EntryComplet->set_text_column(TreeMRecs.col_text);

  mEntry.set_completion(EntryComplet);

  // Для сокращения длины списка выбора можно использовать фильтр:
  //
  // completion->set_match_func(
  //    sigc::mem_fun(*this, &app_win::on_complete_match));

  // Заполнение списка
  unsigned int id = 0;
  Gtk::TreeRow row {};

  row = *(LSRows->append());
  row[TreeMRecs.col_id] = ++id;
  row[TreeMRecs.col_text] = "Adriano Chellentano";

  row = *(LSRows->append());
  row[TreeMRecs.col_id] = ++id;
  row[TreeMRecs.col_text] = "Alan Zee";

  row = *(LSRows->append());
  row[TreeMRecs.col_id] = ++id;
  row[TreeMRecs.col_text] = "Bob Dryoo";

  row = *(LSRows->append());
  row[TreeMRecs.col_id] = ++id;
  row[TreeMRecs.col_text] = "Billy Joe";

  // Возможность предложить выбор дополнительных действий, если в списке
  // не оказалось подходящего элемента. Меню этих действий добавляется
  // в нижнюю часть списка:

  mActions[0] = "Use Wizzard";
  mActions[1] = "Browse file";
  for(const auto& the_pair: mActions)
    EntryComplet->insert_action_text(the_pair.second, the_pair.first);

  EntryComplet->signal_action_activated().connect(sigc::mem_fun(
    *this, &app_win::on_select_action));

  return;
}

///
/// \brief app_win::on_button_close
///
void app_win::on_button_close(void)
{
  hide();
  return;
}

/* You can do more complex matching with a handler like this. For instance, you
 * could check for substrings inside the string instead of the start, or you
 * could look for the key in extra model columns as well as the model column
 * that will be displayed. The code here is not actually more complex - it's
 * a reimplementation of the default behaviour.
 *
bool ExampleWindow::on_completion_match(const Glib::ustring& key, const
        Gtk::TreeModel::const_iterator& iter)
{
  if(iter)
  {
    Gtk::TreeModel::Row row = *iter;

    Glib::ustring::size_type key_length = key.size();
    Glib::ustring filter_string = row[m_Columns.m_col_name];

    Glib::ustring filter_string_start = filter_string.substr(0, key_length);
    //The key is lower-case, even if the user input is not.
    filter_string_start = filter_string_start.lowercase();

    if(key == filter_string_start)
      return true; //A match was found.
  }

  return false; //No match.
}
*/

///
/// \brief app_win::on_completion_activated
/// \param index
///
void app_win::on_select_action(int index)
{
  auto iter = mActions.find(index);
  if(iter != mActions.end())
  {
    Glib::ustring title = iter->second;
    std::cout << "Selected: " << title << std::endl;
  }
  return;
}

app_win::~app_win(void) {return;}
app_win::tree_rec::~tree_rec(void) {return;}
