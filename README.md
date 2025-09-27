# 💻 CODE - C++
This repository is a collection of libraries and classes definitions for programming in **C++**.
<br>
<br>

## ❓ How to use the repo
There is a folder for each library, which contains the *'library.hpp'* and the *'library.cpp'* files.<br>
For each library can be found also a **Makefile**, which will automatize the compilation process.

## ❗ Exceptions Handling
In order to handle in the best way possible all the various exceptions that can occurre when using the libraries, has also been designed a specific **exception-library** named *'myExceptions'*, which is mandatory to include when using all the other ones in order to make them work correctly.<br>
The *'myExceptions'* library contains some custom exceptions, as well as some functions to use in order to eventually catch them.<br>
The library has been implemented in this way in order to make it easy to be used in all the other projects, however it is also avaible for common use, as well as all the other libraries ( if it is included in the project obviously ).
<br>
<br>

## 📖 Contents of the libraries
Here is a list of the libraries wich can be found in the repo, everyone in their subfolder:
### 1. myExceptions
>The core of all the libraries collected in this repository, used in order to managed custom Exceptions.
### 2. myHash
>A library wich allows to create and work with Hash-Tables, following the open/close hashing rules.