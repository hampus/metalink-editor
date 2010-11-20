Metalink Editor 2
=================

This is a rewrite of Metalink Editor 1.x, a GUI editor for metalink files.

Current features
----------------
* Multi-file metalinks.
* Load and save Metalink 4.
* Load and save Metalink 3.
* Edit URLs.
* Add file by scanning a file from a local file system.
* Show and delete piece hashes (only shows count and type).
* Show full file hashes.

Remaining tasks/features
------------------------
* Edit basic file info [partially done].
* Edit full file hashes.
* Load hashes (full and piece hashes).
* Settings for file scanning.
* Optimize scanning for multi-core CPUs.
* Replace OpenSSL, because of its license (Crypto++ looks nice).
* Validate data (real time or before saving) and show a list of errors.
* Create a web site.
* Write documentation (probably some kind of HTML).

Dependencies
------------
* C++ compiler.
* CMake: http://www.cmake.org/
* wxWidgets: http://wxwidgets.org/
* Expat: http://expat.sourceforge.net/
* OpenSSL: http://www.openssl.org/

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

Building from source (Windows)
------------------------------------
For Windows it is a lot easier to download a prebuilt binary. Only advanced
users should try compiling the software on Windows. It is possible to build
it using MinGW/MSYS and CMake.

Running tests
-------------
Run 'make check' to build and run the unit tests. The tests cover some of the
non-GUI source code and require CPPUnit.

Uninstall
---------
Just delete all installed files. You can use 'make uninstall' for this or
simply delete the install directory or similar. Note that make uninstall
doesn't delete any directories (only the files). You can always delete
%prefix%/share/metalinkeditor/ or %prefix% (on Windows) manually, if it bothers
you.

If you installed it using an installer, then please use the provided
uninstaller (usually through the control panel in Windows). Otherwise the
application may still be registered as installed in your system.
