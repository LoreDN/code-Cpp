# :computer: CODE - C++
This repository is a collection of libraries and classes definitions for programming in <strong>C++</strong>.
<br>
<br>

## :question: How to use the repo
The repo is diveded in the following subfolders:<br>
  - <strong>libraries :file_folder: :</strong> this is the core of the repo, in which are collected all the <em>'library.hpp'</em> files, as well as the corresponding <em>'library.cpp'</em> ones. 
    All the libraries are open source, and they start with a brief explanation of how to use them.
  - <strong>functions :heavy_check_mark: :</strong> in this folder can be found all the single functions used in the libraries, everyone in a <em>'function.cpp'</em> file.
<br>

## Exceptions Handling
In order to handle all the custom exceptions that can occurre when using the library, has been designed a <strong>core-library</strong> named <em>'myExceptions'</em>, which is mandatory to download in order to use all the other libraries correctly.
<br>
The <em>'myExceptions'</em> library contains some custom exceptions, as well as some functions to use in order to catch them. The library has been implemented in this way in order to be used in all the other libraries ( and projects ), however this custom exceptions are avaible for general use ( if the library is included in the project obviously ).