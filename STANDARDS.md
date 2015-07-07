**most importantly:** "know when to be inconsistent -- sometimes the style guide just doesn't apply.  When in doubt, use your best judgment.  Look at other examples and decide what looks best.  And don't hesitate to ask!" -- Guido van Rossum, Barry Warsaw, Nick Coghlan.

**Brackets**

1. Allman style broken braces, and avoid unbraced one line conditional statements.
``` C++
if ( condition == true )
{
  ...
}
else
{
 ...
}
```

**Indentation**

1. Do **not** use tabs.  All indentation is of 4 spaces.
2. Class, Namespace, Struct, If, For, Switch, etc.. statements **must** be indented.
``` C++
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

**Comments**

1. Comments **should** be avoided as they add an additional layer of management and/or technical-debt.
2. Commenting is just as ineffective as poorly readable code.
3. Code should be self documenting with descriptive naming conventions applied to functions, variables, files, directories, etc... 
4. Commenting may be a sign you need to split the logic into multiple manageable blocks.

**Properties/Variables**

1. Property and Variables names **must** follow the [Snake-case naming convention](https://en.wikipedia.org/wiki/snake_case).
2. Property and Variables **must** be initialised to a known state on declaration.
``` C++
int limit = 0;
int person_age = 21;
string name = String::empty;
```

**Classes**

1. Class property names **must** be prefixed with `m_` and follow the [Snake-case naming convention](https://en.wikipedia.org/wiki/snake_case).
2. Class properties **must** be initialised to a known state on instance creation.
3. Class properties **must** be private in scope.
4. Class getter/setter accessor methods **must not** return non-const pointers/references.
5. There **must** be **no** using namespace declarations in class header files.
6. Forward declarations are favoured over ```#include``` within class header files; with the exception of the standard template library.
7. Empty method bodies (when unavoidable) shall be marked with a single return.
8. Public classes **must** implement an [opaque pointer](http://en.wikipedia.org/wiki/Opaque_pointer). 
9. Class names **must** start each word boundary with an UPPERCASED letter. 
``` C++
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

**Enumerations**

1. Enumerations **must** be strongly typed.
2. Enumeration fields **must** be UPPERCASED.
3. Enumeration fields **must** be initialised to a known state.
4. Enumeration names **must** start each word boundary with an UPPERCASED letter.
``` C++
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

**Structures**

1. Structure property names **must** follow the [Snake-case naming convention](https://en.wikipedia.org/wiki/snake_case).
2. Structure properties **must** be initialised to a known state on instance creation.
3. Structure names **must** start each word boundary with an UPPERCASED letter. 
``` C++
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

**Methods/Functions**

1. Functions and Methods **must** use the [Snake-case naming convention](https://en.wikipedia.org/wiki/snake_case).
2. Functions and Methods **should** perform one mental operation which is reflected in their name.
3. Function and Method declarations **should** avoid similar argument types.
4. It is recommended that Functions and Methods are no greater than 70 lines of code. If you find that the LOC exceed this limit, it may be an indication that it is performing more than one mental operation; see rule 2. 

``` C++
int ping( Hostname hostname, Interface interface, int16_t port )
{
  auto port = port;
  auto hostname = hostname.to_string( );
  auto interface = hostname.to_string( )
    
  ...
    
  return ttl;
}
```

**Whitespace**

1. Whitespace is free, don't be scared to use it.
``` C++
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

**Pointers/References**

1. Pointers and References **must** be aligned to the data type (left).
``` C++
int* age = nullptr;
char* forename = nullptr;
string& surname = m_surname;
```

**Exceptions**

1. Logic within catch-blocks **must** be short & sweet.
2. Name exceptions per Java styling.
``` C++
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

**Namespaces**

1. **Do not** include entire Namespaces, import only the artifact you're interested in.
2. Namespace names **must only** contain lowercased letters.
``` C++
using std::mutex;
using std::string;
using std::thread;

using namespace restq
{
  ...
}
```

**Optimisation**

1. Avoid premature optimisation, **readable, maintainable code is more important**.
