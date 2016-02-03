
## Clutter

Clutter is a simple command line parser for c++. It aims to provide
clutter-free building blocks for quick construction of a low-level
command line interface.

### Usage

To use a clutter interface, simply initialize the parser with the
command line arguments of the c++ program. 

```cpp
Clutter cl( argc, argv );
```

#####  Required user input
With clutter initialized, the user input options can be defined. Use
the `require(...)` function to define mandatory user input

```cpp
string filename;
int    number;

cl.require( "-f", "--file", inputfile, "Give a filename for loading");
cl.require( "-n", "--number", number,  "Give a number between 1 and 10");
```

#####  Optional user input
Optional user input can be set using the `request(...)` function. Notice
that for optional input a default value is set in the internal variable.

```cpp
float pi = 3.14159265359;
bool  verbose = false;

cl.request( "-p", "--pi",      pi,      "Give the value of pi");
cl.request( "-v", "--verbose", verbose, "Enable verbose mode");
```

#####  Wrapping up
When all command line options have been defined, tell clutter to
finalize the parsing

```cpp
cl.end_parse();
```

If there are any trailing flags that were not interpreted, clutter will
inform the user. If something went wrong during parsing, or if one of
the required options is missing from the command line input, clutter
will throw an error. The entire parsing tree should therefore be wrapped
in a try/catch block just to be safe.

#####  A help flag
You'll note that every require/request call included a note on what the
option does. This is because clutter has a build-in help function that
automatically adds a `-h/--help` flag to every interface. If clutter
sees that a help flag is present in the command line, it will show all
parsing options and terminate the program.

#####  Other features
The usage of both a short(`-l`) and long (`--long`) flag is for
convenience, but defining only one of the two works just fine

```cpp
bool force = false;
cl.request( "", "--force", force, "Force execution" );
```

It is even possible to get a list of entries, for example, a set of
search paths where the program should look for your input file

```cpp
vector<string> search_paths;

cl.request( "-s", "", search_paths, "Enter a list of search paths (space separated)" );
```

At times it is also useful to at a `redial(...)` call to your interface.
```cpp
cl.redial( "executable.name" )
``` 
This function creates a one-line file called 'redial', stating how the program
was last called. Aside from giving a nice bit of memory support, this allows the
program to be easily run with the same settings by using the shell command
`source redial`.

### Installation
Look at the Makefile for install instructions. A proper config/make tool
may follow later.

### Tests & Examples

Look in the `test/` folder for a set of miniature programs that test
every option of the clutter interface. This folder also contains a
complete worked example.
