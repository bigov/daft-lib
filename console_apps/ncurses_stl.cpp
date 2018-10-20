/* ncurses C++
 *
 * A general purpose example of using ncurses in C++ e.g. with STL strings.
 * I guess whatever license ncurses uses applies, otherwise public domain.
 */
 
# include <algorithm>
# include <iostream>
# include <fstream>
# include <iterator>
# include <string>
# include <sstream>
# include <vector>
# include <ncurses.h> // Macros cause compatibility issues with sstream. If you must use them together, include ncurses second.
// Most of these includes/headers/libraries/etc. are not required here. If it doesn't compile without it, you need it.
 
bool curses_started = 0; // Redundant added safety.
bool input_mode_command = 1; // Standard terminal input (1) vs. ncurses reading every character (0).
int row, col;
std::string input; // Global variable to hold current input. String type because UNIX philosophy.
 
auto getinput () -> void // Gets one unit of input at a time. Whether that is one line or one character is dependent on the input mode.
{
        char ch;
        input.clear();
        if (input_mode_command)
        {
                while (1) // Assumes (default) position of cursor is at printing location.
                {
                        ch = getch();
                        if (ch == '\n') // Keeps buffering input until end of line. Check done after acquiring input char (thus if inside while) to prevent it from being discarded automatically.
                        {
                                break;
                        }
                        if (ch == '\a' || ch == '\b') // Ensure normal attempts at backspace are caught.
                        {
                                if (!input.empty()) // pop_back will cause a crash when attempting to remove stuff from an empty vector.
                                {
                                        input.pop_back(); // Removes previously entered character from buffered input.
                                        addch('\b'); // Actual backspacing from user's perspective in these 5 lines.
                                        addch(' ');
                                        int y, x;
                                        getyx (stdscr, y, x);
                                        move (y, x-1); // More than one line of user input deemed unlikely/useless.
                                }
                        }
                        else
                        {
                                input.push_back(ch);
                                addch(ch);
                        }
                }
        }
        else
        {
                ch = getch();
                input.push_back(ch);
        }
}
 
// Alternative functions to ncurses output functions with same naming scheme using STL strings follow. Done for C++11 compatibility and ease-of-use.
 
auto printstr (const std::string &str) -> void
{
        for (char ch : str)
        {
                addch (ch);
        }
}
 
auto mvprintstr (int y, int x, const std::string &str) -> void
{
        move (y, x);
        printstr (str);
}
 
auto mvwprintstr (WINDOW *win, int y, int x, const std::string &str) -> void
{
        wmove (win, y, x);
        printstr (str);
}
 
auto wprintstr (WINDOW *win, const std::string &str) -> void
{
        int y, x;
        getyx (win, y, x);
        mvwprintstr (win, y, x, str);
}
 
auto endCurses () -> void
{
        if (curses_started && !isendwin())
        {
                endwin();
        }
}
 
auto startCurses () -> void
{
        if (curses_started)
        {
                refresh();
        }
        else // IMO most powerful defaults
        {
                initscr();
                raw();
                noecho();
                keypad(stdscr, 1);
                atexit(endCurses);
                curses_started = 1;
        }
}
 
auto init_color_pairs () -> void // To initialise all colors using a easy-to-memorize naming scheme.
{
        short f, b; // For foreground and background respectively.
        for ( f = 0; f < COLORS; ++f )
        {
                for ( b = 0; b < COLORS; ++b )
                {
                        init_pair ( f * COLORS + b, f, b );
                }
        }
}
 
auto main () -> int
{
        startCurses();
        if(!has_colors()) // Harsh redundant safety check.
        {
                endCurses();
                std::cout << "Your terminal does not support color" << std::endl;
                return 1;
        }
        start_color();
        init_color_pairs();
        getmaxyx(stdscr,row,col);
        while (1)
        {
                getinput();
                if (input == ":exit") // Makes rerunning tests easy when program messes up but doesn't crash.
                {
                        return 0;
                }
                printstr (input); // Insert your "apply input" function(s) here.
        }
        endCurses(); // Even more redundant safety. Also because the return is mandatory anyways.
        return 1;
}
 
/* Further notes:
 *      Use of windows and other things could be generalised better.
 *      This is a non-exhausive and amateur example.
 *      A lot of this was taken from the public domain.
 */