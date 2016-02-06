
## Clutter

Clutter is a simple command line parser for c++. It aims to provide a simple
framework that can be used to quickly construct a clutter-free low-level
command line interface. 

### Usage

To use a Clutter interface, simply initialize the parser with the
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
that for optional input the associated variable has a default value.

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

If something went wrong during parsing, Clutter will throw a exception
stating what went wrong and which command line option was involved. Possible
error are:
- A required option was not provided
- An option in the command line was not recognized by Clutter
- An option flag appeared twice in the command line

#####  A help flag
Every `require()` and `request()` call includes a note on what the option
does. This information is used by Clutter to provide a build-in help function
that automatically adds a `-h/--help` flag to every interface. If Clutter
sees that a help flag is present in the command line, it will show all
parsing options and automatically terminate the program.

#####  Other features

* **Single option flags**  
    The usage of both short (`-s`) and long (`--long`) flags is for
    convenience. Defining only one of the two works just fine

    ```cpp
    bool force = false;
    cl.request( "", "--force", force, "Force execution" );
    ```

* **Input lists**  
    It is also possible to get a list of entries, for example, a set of
    search paths where the program should look for your input file

    ```cpp
    vector<string> search_paths;

    cl.request( "-s", "", search_paths, "Enter a list of search paths (space separated)" );
    ```
    
    Only standard vector containers are supported at this time.

* **Command line redial**  
    Clutter also offers a *redial* functionality. This function creates a 
    one-line file containing the command line used to call the program. Aside 
    from providing a nice bit of memory support, this allows the program to be 
    easily run again using the previous settings. The redial option is used as
    ```cpp
    cl.redial( "my_redial.file" );
    ```
    Optionally the filename can be left out. In that case Clutter will use 
    the default name 'redial'. To execute the redial, one can, for example,
    use the shell command `source redial`.

### Installation
Look at the Makefile for install instructions. A proper config/make tool
may follow later.

### Tests & Examples

Look in the `test/` folder for a complete worked example.
