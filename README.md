# 💻 CODE - C++
This repository is a collection of libraries and classes definitions for programming in **C++**.
<br>
<br>

## ❓ How to use the repo
There is a folder for each library, which contains the `library.hpp` and the `library.cpp` files.<br>
For each library can be found also a **Makefile**, which will automatize the compilation process.

## ❗ Exceptions Handling
In order to handle in the best way possible all the various exceptions that can occurre when using the libraries, has also been designed a specific **exception-library** named `myExceptions`, which is mandatory to include when using all the other ones in order to make them work correctly.<br>
The `myExceptions` library contains some custom exceptions, as well as some functions to use in order to eventually catch them.<br>
The library has been implemented in this way in order to make it easy to be used in all the other projects, however it is also avaible for common use, as well as all the other libraries ( if it is included in the project obviously ).
<br>
<br>

# 📦 Packages Releases
In order to make as easy as possible to get and use the libraries, the only thing that the user needs to do is to install the wanted *.deb* package.<br>
It can be done with the following **bash** commands:

```bash
# change LIB / PACKAGE with the wanted ones (as myExceptions / myexceptions)

# download the wanted package
wget https://github.com/LoreDN/code-Cpp/releases/download/LIB/PACKAGE.deb

# install the package
sudo dpkg -i PACKAGE.deb

# add the "LDN" subfolder path to the linker paths
echo "/usr/lib/LDN" | sudo tee /etc/ld.so.conf.d/ldn.conf
sudo ldconfig
```

Finally, in order to compile your program using the library, all you have left to do is to add this command to the compilation one:

```bash
# -I/usr/include/LDN adds the /usr/include/LDN/ folder to the include paths (you can also #include <LDN/myLIB>)
# -L/usr/lib/LDN adds the /usr/lib/LDN/ folder to the linking paths (in order to use the library -lLIB)

# -lLIB indicates the library binary file, you have to change LIB with the wanted one (as myExceptions)
g++ main.cpp -o program -I/usr/lib/LDN -L/usr/lib/LDN -lLIB
```

<br>
<br>

## 📖 Contents of the libraries
Here is a list of the libraries wich can be found in the repo, everyone in their subfolder:<br>

### 1. myExceptions
The core of all the libraries collected in this repository, used in order to managed custom Exceptions.

```bash
# latest v2.0
wget https://github.com/LoreDN/code-Cpp/releases/download/myExceptions/myexceptions.deb
sudo dpkg -i myexceptions.deb

# update linker path
echo "/usr/lib/LDN" | sudo tee /etc/ld.so.conf.d/ldn.conf
sudo ldconfig
```

### 2. myHash
A library wich allows to create and work with Hash-Tables, following the open/close hashing rules.

```bash
# latest v1.0
wget https://github.com/LoreDN/code-Cpp/releases/download/myHash/myhash.deb
sudo dpkg -i myhash.deb

# update linker path
echo "/usr/lib/LDN" | sudo tee /etc/ld.so.conf.d/ldn.conf
sudo ldconfig
```

### 3. myHeap
A library wich allows to create and work with Heaps, implementing both Min-Heap and Max-Heap.

```bash
# latest v1.0
wget https://github.com/LoreDN/code-Cpp/releases/download/myHeap/myheap.deb
sudo dpkg -i myheap.deb

# update linker path
echo "/usr/lib/LDN" | sudo tee /etc/ld.so.conf.d/ldn.conf
sudo ldconfig
```