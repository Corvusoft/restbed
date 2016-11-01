Overview
--------

This document sets out the expected coding style for those who wish to participate in this project. With this standard we will maintain a readable codebase that can be easily cannibalised by new and old developers alike.

To ensure the codebase meets this standard please install the supplied [GIT pre-commit](https://git-scm.com/book/en/v2/Customizing-Git-Git-Hooks) hook into your local copy. You're also required to install the [Artistic Style](http://astyle.sourceforge.net/) tool on your system for this hook to be successful; you must have version 2.05 or greater installed.

```
cd restbed/
cp tool/git/pre-commit .git/hooks
chmod +x .git/hooks/pre-commit
```

**most importantly:** "know when to be inconsistent -- sometimes the style guide just doesn't apply. When in doubt, use your best judgment. Look at other examples and decide what looks best. And don't hesitate to ask!" -- Guido van Rossum, Barry Warsaw, Nick Coghlan.

Interpretation
--------------

The key words “MUST”, “MUST NOT”, “REQUIRED”, “SHALL”, “SHALL NOT”, “SHOULD”, “SHOULD NOT”, “RECOMMENDED”, “MAY”, and “OPTIONAL” in this document are to be interpreted as described in [RFC 2119](http://tools.ietf.org/pdf/rfc2119.pdf).

Table of Contents
-----------------

1.	[Overview](#overview)
2.	[Interpretation](#interpretation)
3.	[Brackets](#brackets)
4.	[Indentation](#indentation)
5.	[Comments](#comments)
6.	[Properties/Variables](#propertiesvariables)
7.	[Classes](#classes)
8.	[Enumerations](#enumerations)
9.	[Structures](#structures)
10.	[Methods/Functions](#methodsfunctions)
11.	[Whitespace](#whitespace)
12.	[Pointers/References](#pointersreferences)
13.	[Exceptions](#exceptions)
14.	[Namespaces](#namespaces)
15.	[Optimisations](#optimisations)

### Brackets

-	Allman style broken braces, and avoid unbraced one line conditional statements.

```C++
if ( condition == true )
{
  ...
}
else
{
 ...
}
```

### Indentation

-	Do **not** use tabs. All indentation is of 4 spaces.
-	Class, Namespace, Struct, If, For, Switch, etc.. statements **must** be indented.

```C++
namespace transport
{
  class Car( void )
  {
    public:
      Car( const int number_of_wheels ) : m_number_of_wheels
      {
        switch( m_number_of_wheels )
        {
            case 1:
              break;
            default:
              break;
        }
      }

    private:
      uint8_t m_number_of_wheels;
  }
}
```

### Comments

-	Comments **should** be avoided as they add an additional layer of management and/or technical-debt.
-	Commenting is just as ineffective as poorly readable code.
-	Code should be self documenting with descriptive naming conventions applied to functions, variables, files, directories, etc...
-	Commenting may be a sign you need to split the logic into multiple manageable blocks.

### Properties/Variables

-	Property and Variables names **must** follow the [Snake-case naming convention](https://en.wikipedia.org/wiki/snake_case).
-	Property and Variables **must** be initialised to a known state on declaration.

```C++
int limit = 0;
int person_age = 21;
string name = String::empty;
```

### Classes

-	Class property names **must** be prefixed with `m_` and follow the [Snake-case naming convention](https://en.wikipedia.org/wiki/snake_case).
-	Class properties **must** be initialised to a known state on instance creation.
-	Class properties **must** be private in scope.
-	Class getter/setter accessor methods **must not** return non-const pointers/references.
-	There **must** be **no** using namespace declarations in class header files.
-	Forward declarations are favoured over `#include` within class header files; with the exception of the standard template library.
-	Empty method bodies (when unavoidable) *shall* be marked with a single return.
-	Public classes **must** implement an [opaque pointer](http://en.wikipedia.org/wiki/Opaque_pointer).
-	Class names **must** start each word boundary with an UPPERCASED letter.

```C++
class Person
{
  public:
    Person( void ) : m_age( 0 )
    {
      return;
    }

    int get_age( void ) const
    {
      return m_age;
    }

    void set_age( const int value )
    {
      m_age = value;
    }

  private:
    int m_age;.
}
```

### Enumerations

-	Enumerations **must** be strongly typed.
-	Enumeration fields **must** be UPPERCASED.
-	Enumeration fields **must** be initialised to a known state.
-	Enumeration names **must** start each word boundary with an UPPERCASED letter.

```C++
enum LogLevel : int
{
  INFO = 0000,
  DEBUG = 1000,
  FATAL = 2000,
  ERROR = 3000,
  WARNING = 4000,
  SECURITY = 5000
}
```

### Structures

-	Structure property names **must** follow the [Snake-case naming convention](https://en.wikipedia.org/wiki/snake_case).
-	Structure properties **must** be initialised to a known state on instance creation.
-	Structure names **must** start each word boundary with an UPPERCASED letter.

```C++
struct HttpRequest
{
  Bytes body = { };
  uint16_t port = 80;
  double version = 1.1;
  std::string host = "";
  std::string path = "/";
  std::string method = "GET";
  std::multimap< std::string, std::string > headers { };
}
```

### Methods/Functions

-	Functions and Methods **must** use the [Snake-case naming convention](https://en.wikipedia.org/wiki/snake_case).
-	Functions and Methods **should** perform one mental operation which is reflected in their name.
-	Function and Method declarations **should** avoid similar argument types.
-	It is recommended that Functions and Methods are no greater than 70 lines of code. If you find that the [LOC](https://en.wikipedia.org/wiki/Source_lines_of_code) exceed this limit, it may be an indication that it is performing more than one mental operation; see rule 2.

```C++
int ping( Hostname hostname, Interface interface, int16_t port )
{
  auto port = port;
  auto hostname = hostname.to_string( );
  auto interface = hostname.to_string( )

  ...

  return ttl;
}
```

### Whitespace

-	Whitespace is free, don't be scared to use it.

```C++
int process_exit_status = 0;
const string filename = "/bin/ls";

do
{
  Process reaction = load_process( filename );
  reaction.run( );

  process_exit_status = reaction.get_exit_status( );
}
while ( process_exit_status not_eq -1 );
```

### Pointers/References

-	Pointers and References **must** be aligned to the data type (left).

```C++
int* age = nullptr;
char* forename = nullptr;
string& surname = m_surname;
```

### Exceptions

-	Logic within catch-blocks **must** be short & sweet.
-	Name exceptions per Java styling.

```C++
try
{
  start( );
}
catch ( const invalid_argument& ia )
{
  stop( );
}
catch ( const runtime_error& re )
{
  stop( );
}
catch ( const exception& ex )
{
  stop( );
}
```

### Namespaces

-	**Do not** include entire Namespaces, import only the artifact you're interested in.
-	Namespace names **must only** contain lowercased letters.

```C++
using std::mutex;
using std::string;
using std::thread;

using namespace restbed
{
  ...
}
```

### Optimisations

-	Avoid premature optimisation, **readable, maintainable code is more important**.
