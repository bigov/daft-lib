#
# TrickRig Sqlite3 wraper testing
#
cmake_minimum_required( VERSION 3.0 )
project( tr_sqli3_wr )

ADD_LIBRARY( sqlite3w SHARED "sqlite3w.cpp" "sqlite3.c" )
add_executable( testing "main.cpp" )
target_link_libraries( testing sqlite3w )
