QBox2D
======

An attempt to use Erin Catto's Box2D (http://www.box2d.org) API with Qt/C++ Graphics VIew Framework



## References:

This program was based on Erin Catto's Box2D (http://www.box2d.org) API

Angle computation was based on Thorbjørn Lindeijer's Box2D QML Plugin (https://github.com/bjorn/qml-box2d)

Simulation was based on "timerEvent" implementation found at a blog at http://blog.qt.digia.com/blog/2010/02/26/qt-box2d-is-easy/ wherein an archive can be seen on a comment (http://boulabiar.net/box2d/Box2Dm.7z).

## Binaries:

First program I coded

https://www.dropbox.com/s/itdj4b4s0aagfex/QBox2D.exe

QTestbed (incomplete implementation of Testbed)

https://www.dropbox.com/s/evvbyfr4a1ryxxf/QTestbed.exe

The above executables were built under Qt4.8.4/VS2012... therefore update your VC++ Runtime if it asks for a dll

Use this link (http://www.microsoft.com/en-us/download/details.aspx?id=30679) or google it :)

## Usage:

Simply include qbox2d.pri into your project

Don't forget to add qbox2dworld.h, qbox2dbody.h, etc. headers

Follow the conventional Box2D coding but modify function calls by changing the first letter into lowercase (e.g. CreateBody into createBody). Qt coding style is used instead of Box2D's when it comes to funcction calls.

Replace b2Body with QBox2DBody, and b2World with QBox2DWorld. These are just the currently supported classes. For future versions, replace "b2" prefix with "QBox2D".

