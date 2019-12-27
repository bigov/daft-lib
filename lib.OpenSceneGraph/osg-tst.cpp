/*
 * pacman -S mingw-w64-x86_64-osgworks-debug-git \
 *           mingw-w64-x86_64-osgocean-debug-git \
 *           mingw-w64-x86_64-osgearth-debug \
 *           mingw-w64-x86_64-osgbullet-debug-git \
 *           mingw-w64-x86_64-OpenSceneGraph-debug
 *
 * pkg-config --libs openscenegraph-osgViewer
 * -LC:/msys64/mingw64/lib -losgViewer -losgText -losgGA -losgDB -losgUtil -losg -lOpenThreads
 *
 * Соответственно:
 *
 * c++ osg-tst.cpp -o tst.exe -LC:/msys64/mingw64/lib -losgViewer -losgText \
 *     -losgGA -losgDB -losgUtil -losg -lOpenThreads
 *
 */

#include <iostream>
#include <osgViewer/Viewer>

int main()
{
    osgViewer::Viewer viewer;
    return viewer.run();
}
