MIT License

Copyright (c) 2021 Nicola Pancheri
pancheri.nicola@gmail.com 

MVCqt is an tiny framework written in C++/Qt (v.5.15.2) to develop desktop
applications as if they were web applications. The idea is to keep using HTML/CSS/JS even for
the interface of the desktop applications (but without the need to start an http server).
This library has been built trying to following the MVC design pattern;
the MVCqtView instantiate a QWebEngineView object (a qt widget that is used to view and edit web documents)
to show the frontend part of the program; the MVCqtModel is the backend, the logic behind your application and you must derive it and pass your derived class to the framework. The MVCqtController configures and connects MVCqtView and MVCqtModel using qt signals and slots.

This library has been written for my self but if you like/don't like it let me know. :)

All the following instructions are to be run inside the Src dir of the project

Compiling instructions:
 $ make

Install instructions:
 $ make install

Uninstall instructions:
 $ make uninstall


Compiling the single components for unit tests:
 A) Compiling and installing actor:
  $ make actor && make install
 B) Compiling and installing model:
  $ make model && make install
 C) Compiling and installing view:
  $ make view && make install
 D) Compiling and installing controller:
  $ make controller && make install

HOW TO USE:
Implement the backend of your application composing all the objects that you use in a big class
derived from MVCqtModel.
Import MVCqt.h and create an object of type MVCqt passing your wrapper class as parameter of the constructor.
MVCqt.start() to run the application.
