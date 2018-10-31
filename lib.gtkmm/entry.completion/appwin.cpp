/* Filename: appwin.cpp
 *
 */
#include "appwin.hpp"

app_win::app_win(void)
{
  set_size_request(200, 200);
  set_title("EntryCompletion demo");
  set_border_width(8);

  add(mVBox);

  mEntry.set_max_length(50);
  mEntry.set_text("Hello");

  //mVBox.add(mEntry);
  mVBox.pack_start(mEntry, Gtk::PACK_SHRINK);
  mVBox.pack_start(mLabel, Gtk::PACK_EXPAND_WIDGET);

  mVBox.add(mHBox);
  mHBox.set_border_width(8);

  mHBox.add(mCheckButtonEditable);
  mCheckButtonEditable.signal_toggled().connect(
    sigc::mem_fun(*this, &app_win::on_chexkbox_editable_toggled));
  mCheckButtonEditable.set_active(true);

  mHBox.add(mCheckButtonVisible);
  mCheckButtonVisible.signal_toggled().connect(
    sigc::mem_fun(*this, &app_win::on_checkbox_visibility_toggled));
  mCheckButtonVisible.set_active(true);

  mVBox.pack_start(mButtonClose, Gtk::PACK_SHRINK);

  mButtonClose.signal_clicked().connect(
    sigc::mem_fun(*this, &app_win::on_button_close));
  mButtonClose.set_can_default();
  mButtonClose.grab_default();

  auto completion = Gtk::EntryCompletion::create();
  mEntry.set_completion(completion);

  // Создание списка полей
  auto refCompletionModel = Gtk::ListStore::create(TreeModColRecord);
  completion->set_model(refCompletionModel);

  // можно использовать фильтр отбора полей
  // completion->set_match_func(
  //    sigc::mem_fun(*this, &app_win::on_complete_match));

  // Заполнение списка
  unsigned int id = 0; auto

  row = *(refCompletionModel->append());
  row[TreeModColRecord.m_col_id] = ++id;
  row[TreeModColRecord.m_col_name] = "Adriano Chellentano";

  row = *(refCompletionModel->append());
  row[TreeModColRecord.m_col_id] = ++id;
  row[TreeModColRecord.m_col_name] = "Alan Zee";

  row = *(refCompletionModel->append());
  row[TreeModColRecord.m_col_id] = ++id;
  row[TreeModColRecord.m_col_name] = "Bob Dryoo";

  row = *(refCompletionModel->append());
  row[TreeModColRecord.m_col_id] = ++id;
  row[TreeModColRecord.m_col_name] = "Billy Joe";

  //Tell the completion what model column to use to
  //- look for a match (when we use the default matching, instead of
  //  set_match_func().
  //- display text in the entry when a match is found.
  completion->set_text_column(TreeModColRecord.m_col_name);

  mCompletionActions[0] = "Use Wizzard";
  mCompletionActions[1] = "Browse file";

  for(const auto& the_pair: mCompletionActions)
  {
    auto row_id = the_pair.first;
    auto title  = the_pair.second;
    completion->insert_action_text(title, row_id);
  }

  completion->signal_action_activated().connect(sigc::mem_fun(
    *this, &app_win::on_completion_activated));

  show_all_children();

  return;
}

void app_win::on_checkbox_visibility_toggled(void)
{
  mEntry.set_visibility(mCheckButtonVisible.get_active());
  return;
}

void app_win::on_chexkbox_editable_toggled(void)
{
  mEntry.set_editable(mCheckButtonEditable.get_active());
  return;
}

void app_win::on_button_close(void)
{
  hide();
  return;
}

/* You can do more complex matching with a handler like this.
 * For instance, you could check for substrings inside the string instead of the start,
 * or you could look for the key in extra model columns as well as the model column that will be displayed.
 * The code here is not actually more complex - it's a reimplementation of the default behaviour.
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

//
//
void app_win::on_completion_activated(int index)
{
  type_actions_map::iterator iter = mCompletionActions.find(index);
  if(iter != mCompletionActions.end())
  {
    Glib::ustring title = iter->second;
    std::cout << "Selected: " << title << std::endl;
  }
  return;
}

