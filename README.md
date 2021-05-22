MVCqt is an tiny framework written in C++/Qt (v.5.15.2) to develop desktop 
applications as if they were web applications. The idea is to keep using HTML/CSS/JS even for
the interface of the desktop applications (but without the need to start an http server).
This library has been built trying to following the MVC design pattern;
the MVCqtView instantiate a QWebEngineView object (a qt widget that is used to view and edit web documents)
to show the frontend part of the program; the MVCqtModel is the backend, the logic behind your application and you must derive it and pass your derived class to the framework. The MVCqtController configures and connects MVCqtView and MVCqtModel using qt signals and slots. 

This library has been written for my self but if you like/don't like it let me know. :)


Compiling instructions:
 - cd Src
 - ./compile.sh

Install instructions:
- cd Lib
- ./install.sh

Clean instructions:
- cd Lib
- ./clean.sh

Uninstall instructions:
- cd Lib
- ./uninstall.sh


HOW TO USE:
Implement the backend of your application composing all the objects that you use in a big class
derived from MVCqtModel.
Import MVCqt.h and create an object of type MVCqt passing your wrapper class as parameter of the constructor.
MVCqt.start() to run the application.
