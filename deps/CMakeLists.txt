#
# Этот файл необходим для настройки локальной (для конкретного хоста)
# переменной "TP_LIBS" (путь к каталогу внешних библиотек), которая
# устанавливается при помощи команды
#
#    SET( TP_LIBS "D:/dev/WORKSPACE/LIBS" )
#
# в игнорирумом git файле:
#
include( "${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt.user.tp_libs" )

