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

## Using SMTPlan

SMTPlan is suited to domains with continuous polyomial change over real variables.

To run SMTPlan:
```
./SMTPlan [domain_file.pddl] [problem_file.pddl] [options]
```

The possible options are described below:
```
Options:
	-h			Print this and exit.
	-l	number	Begin iterative deepening at an encoding with l happenings (default 1).
	-u	number	Run iterative deepening until the u is reached. Set -1 for unlimited (default -1).
	-c	number	Limit the length of the concurrent cascading event and action chain (default 2, minimum 2).
	-s	number	Iteratively deepen with a step size of s (default 1).
	-n			Do not solve. Output encoding in smt2 format and exit.
	-v			Verbose times.
```

For example: `./SMTPlan domain.pddl problem.pddl -l 4 -u 10 -s 2`

## More information

For more information on SMTPlan, visit the website: http://kcl-planning.github.io/SMTPlan/
