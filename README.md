# penning_trap
![License](https://img.shields.io/github/license/CloriCaprile/penning_trap)
![Language](https://img.shields.io/badge/language-c%2B%2B-blue)
![Size](https://img.shields.io/github/repo-size/CloriCaprile/penning_trap)

Basic implementation of a simulated Penning trap in C++.
This repo is mantained by group 100 of the course FYS3150/4150 at UiO.

## Table of contents

- [Requirements](#requirements)
- [Building](#building)
- [Tests](#tests)
- [Aknowledgements](#aknowledgements)
- [License](#license)

## Requirements

In order to be able to run everything succesfully you will need:
* A `C++11` compiler
* `armadillo`, an efficient linear algebra library
* `cmake`, for building (optional, recommended)

## Building

Clone this repo with

```bash
git clone https://github.com/CloriCaprile/penning_trap.git
```

or

```bash
git clone git@github.com:CloriCaprile/penning_trap.git
```

### g++

You can compile and link with `g++`.

```bash
g++ main.cpp src/*.cpp -I include -larmadillo -o penningtrap
```
You might need to add the  `-std=gnu++11` if you are a Mac user.
You can then run the executable with

```bash
./penningtrap
```

### CMAKE

Alternatively you can build everything with `cmake`. First you need to create a `build/` directory and move into it
```bash
mkdir build; cd build
```
Now you just need to run
```bash
cmake ..
```
If it outputs correctly you should be able to build the project by runnning
```bash
make
```
from the same `build/` directory. In this way everything is well organized into specific folders: in the `build/` directory you can find all executables; in the  `include/` all the header files; and in the `test/` directory are stored the tests for most of the functions implemented.

## Tests
CMake provides an easy command for code testing, i.e. from `build/` you can run
```bash
ctest
```
In this way all tests are run.
## Aknowledgements
<button  style="border: transparent; background-color: transparent;">
  <a href=https://github.com/CloriCaprile>Clori</a>
  <div float=left>
    <img src="https://avatars.githubusercontent.com/u/51904841?v=4" margin=0 width=50> 
  </div>
</button>
<button style="border: transparent; background-color: transparent;">
  <a href=https://github.com/diegoscantam>Diego</a>
  <div float=center>
    <img src="https://avatars.githubusercontent.com/u/112166702?v=" width=50> 
  </div>
</button>
<button style="border: transparent; background-color: transparent;">
  <a href=https://github.com/ngrlcu>Luca</a>
  <div>
    <img src="https://avatars.githubusercontent.com/u/79975678?s=400&u=6770b5f0354ed29bf9a54e7f27a8250bb812c279&v=4" width=50> 
  </div>
</button>
<button style="border: transparent; background-color: transparent;">
  <a href=https://github.com/martapisci>Marta</a>
  <div>
    <img src="https://avatars.githubusercontent.com/u/112163092?v=4" width=50>
  </div>
</button>





## License

The code here presented is released under version 3 of the [GNU General Public License](https://www.gnu.org/licenses/gpl-3.0.html).
