MIT License

Copyright (c) 2021 Nicola Pancheri
pancheri.nicola@gmail.com 

<pre>
MVCqt is an tiny framework written in C++/Qt (v.5.15.2) to develop desktop
applications as if they were web applications. The idea is to keep using HTML/CSS/JS even for
the interface of the desktop applications (but without the need to start an http server).
This library has been built trying to following the MVC design pattern;
the MVCqtView instantiate a QWebEngineView object (a qt widget that is used to view and edit 
web documents) to show the frontend part of the program; the MVCqtModel is the backend, 
the logic behind your application and you must derive it and pass your derived class to the framework. 
The MVCqtController configures and connects MVCqtView and MVCqtModel using qt signals and slots.

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

I'm the directory Examples you will find a bounch of mini-app that will help to give you
an idea of how this framework works but lets start from zero...

I'll take the example called Webpage as a model(you'll find it into Examples/Webpage);
The aim of MVCqt is to give an enviroment to develop a desktop application with a GUI using
the MVC design pattern and implementing the model using C++ and the view using HTML/CSS/JS 
as we do for the webapps. Even though I'm using Qt this library should keep it hidden as 
much as possible to the user that should be able to use any language that allows 
to import a c++ library. The idea is that the GUI that everyone develop using the standard
programming languages not created for the GUI are always shitty compared to a web interface
and the code more complicate. Would be much more better, for my point of view, using it as 
a standard everywhere (I mean in desktop enviroment) for the development of the GUI. 
Another constrain that I want is that the output of my compilation (from the framework point 
of view) has to be only a binary and not a bunch of file that can be changed by the final user etc...
Here is where Qt enters: it allows to embedded in the binary the external resources of a project
(html, ccs, js and what ever files that are not C++), has a cool signaling sistem and offer
the class QtWebEngineView, a widget that is used to view and edit web documents.
Water, salt, stir, 15 min in the oven and then you have MVCqt.


Implement the backend of your application composing all the objects that you use in a big class
derived from MVCqtModel.
Import MVCqt.h and create an object of type MVCqt passing your wrapper class as parameter of the constructor.
MVCqt.start() to run the application.

</pre>
