## Installation

SMTPlan requires the Piranha computer algebra system and the z3 SMT solver.

First install z3:
```
git clone https://github.com/Z3Prover/z3
```
And follow the installation instructions for that repository.

Then install Piranha:
```
git clone https://github.com/bluescarni/piranha
```
And follow the installation instructions here: http://bluescarni.github.io/piranha/sphinx/getting_started.html

Then, from the SMTPlan directory:
```
mkdir build
cd build
cmake ..
make
```
