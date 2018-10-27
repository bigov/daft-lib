/* Filename: appwin.hpp
 *
 */
#ifndef APPWIN_HPP
#define APPWIN_HPP

#include <gtkmm.h>

///
/// \brief The app_win class
///
class app_win: public Gtk::Window
{
  public:
    app_win();
    ~app_win() {}

  protected:
    //Signal handlers:
    void on_checkbutton_toggled(void);
    void on_combo_position(void);
    void on_adjustment1_value_changed(void);
    void on_adjustment2_value_changed(void);
    void on_button_quit(void);

    //Member wigets:
    Gtk::Box
      m_VBox_Top {Gtk::ORIENTATION_VERTICAL, 0},
      m_VBox2 {Gtk::ORIENTATION_VERTICAL, 20},
      m_VBox_HScale {Gtk::ORIENTATION_VERTICAL, 10},
      m_HBox_Scales {Gtk::ORIENTATION_HORIZONTAL, 10},
      m_HBox_Combo {Gtk::ORIENTATION_HORIZONTAL, 10},
      m_HBox_Digits {Gtk::ORIENTATION_HORIZONTAL, 10},
      m_HBox_PageSize {Gtk::ORIENTATION_HORIZONTAL, 10};

    Glib::RefPtr<Gtk::Adjustment>
      m_adjustment {Gtk::Adjustment::create(0.0, 0.0, 101.0, 0.1, 1.0, 1.0)},
      m_adjustment_digits {Gtk::Adjustment::create(1.0, 0.0, 5.0, 1.0, 2.0)},
      m_adjustment_pagesize {Gtk::Adjustment::create(1.0, 1.0, 101.0)};

    Gtk::Scale
      m_VScale {m_adjustment, Gtk::ORIENTATION_VERTICAL},
      m_HScale {m_adjustment, Gtk::ORIENTATION_HORIZONTAL},
      m_Scale_Digits {m_adjustment_digits},
      m_Scale_PageSize {m_adjustment_pagesize};

    Gtk::CheckButton m_CheckButton {"Display value on scale widgets", 0};
    Gtk::Scrollbar m_Scrollbar {m_adjustment};
    Gtk::Separator m_Separator {};
    Gtk::ComboBox ComboBoxPosition {};
    Gtk::Button m_Button_Quit {"Quit"};

    ///
    /// Tree model columns:
    ///
    class tree_columns : public Gtk::TreeModel::ColumnRecord
    {
      public:
        Gtk::TreeModelColumn<Gtk::PositionType> PosType {};
        Gtk::TreeModelColumn<Glib::ustring> ColTitle {};

        tree_columns()
        {
          add(PosType);
          add(ColTitle);
        }

    };
    tree_columns TreeColumns {};
    Glib::RefPtr<Gtk::ListStore> refTreeColumns {Gtk::ListStore::create(TreeColumns)};
};

#endif // APPWIN_HPP
