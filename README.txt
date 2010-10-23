Metalink Editor 2
=================

This is a rewrite of Metalink Editor 1.x, a GUI editor for metalink files.

The editor is not yet finished and currently lacks many useful features.

Features
--------
* Multi-file metalinks.
* Load and save Metalink 4.
* Edit URLs.

Planned features
----------------
* Load and save Metalink 3.
* Edit basic file info.
* Edit full file hashes.
* Show and delete piece hashes.
* Add file by scanning a file from a local file system.

Dependencies
------------
* C++ compiler.
* CMake: http://www.cmake.org/
* wxWidgets: http://wxwidgets.org/
* Expat: http://expat.sourceforge.net/

Building from source (Unix)
---------------------------
The following should work well for most people. First use the CMake GUI to
generate Unix Makefiles. Optionally set CMAKE_BUILD_TYPE to "Release" and
CMAKE_INSTALL_PREFIX to a directory where you want it to be installed (makes it
very easy to remove the application). It is also a good idea to use a separate
build directory (e.g. a sub directory of the source code directory).

Now you just need to run "make install" in the build directory. The executable
will be named %prefix%/bin/metalinkeditor. Run it to start the application.

Note that you cannot move the installed application. It won't work if you do.

Building from source (Visual Studio)
------------------------------------
This is for Windows and works well with the free Express edition. First install
and compile wxWidgets and then install Expat. Now run the CMake GUI. You will
probably need to specify some library paths. Optionally set CMAKE_BUILD_TYPE to
"Release" and CMAKE_INSTALL_PREFIX to a directory where you want it to be
installed (e.g. a sub directory to the build directory; it can safely be moved
later). Generate a Visual Studio project and then compile it!

As for Unix, it is generally a good idea to use a separate build directory,
e.g. a sub directory of the source code directory.

For Windows it is a lot easier to download a prebuilt binary. Only advanced
users should try compiling the software on Windows.

Uninstall
---------
Just delete all installed files. You can use 'make uninstall' for this or
simply delete the install directory or similar. Note that make uninstall
doesn't delete any directories (only the files). You can always delete
%prefix%/share/metalinkeditor/ or %prefix% manually, if it bothers you.

If you installed it using an installer, then please use the provided
uninstaller. Otherwise the application may still be registered as installed in
your system.
