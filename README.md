# :computer: CODE - C++
This repository is a collection of libraries and classes definitions for programming in <strong>C++</strong>.
<br>
<br>

## :question: How to use the repo
The repo is diveded in the following subfolders:<br>
  - <strong>libraries :file_folder: :</strong> this is the core of the repo, in which are collected all the <em>'library.hpp'</em> files, as well as the corresponding <em>'library.cpp'</em> ones. 
    All the libraries are open source, and they start with a brief explanation of how to use them.
  - <strong>classes :heavy_check_mark: :</strong> in this folder can be found all the single classes ( together with the related stan-alone functions ) used in the libraries, everyone in a <em>'class.cpp'</em> file.
<br>

## :exclamation: Exceptions Handling
In order to handle in the best way possible all the various exceptions that can occurre when using the libraries, has also been designed a specific <strong>exception-library</strong> named <em>'myExceptions'</em>, which is mandatory to include when using all the other ones in order to make them work correctly.
<br>
The <em>'myExceptions'</em> library contains some custom exceptions, as well as some functions to use in order to eventually catch them. The library has been implemented in this way in order to make it easy to be used in all the other projects, however it is also avaible for common use, as well as all the other libraries ( if it is included in the project obviously ).
<br>
<br>

## :open_book: Contents of the libraries
Here is a list of the libraries wich can be found in the repo, everyone in their subfolder:
### 1. <strong>myExceptions</strong>
>The core of all the libraries collected in this repository.
### 2. <strong>myHash</strong>
>A library wich allows to create and work with Hash Tables, following the open hashing rules.