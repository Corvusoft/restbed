Overview
--------

This document is intended to accurately communicate the [Application Programming Interface (API)](https://en.wikipedia.org/wiki/Application_programming_interface) exposed by the Restbed framework for public consumption.

A description of the frameworks software architecture is provided by the [Design Overview](#DESIGN.md) documentation.

Interpretation
--------------

The key words “MUST”, “MUST NOT”, “REQUIRED”, “SHALL”, “SHALL NOT”, “SHOULD”, “SHOULD NOT”, “RECOMMENDED”, “MAY”, and “OPTIONAL” in this document are to be interpreted as described in [RFC 2119](http://tools.ietf.org/pdf/rfc2119.pdf).

Table of Contents
-----------------

1.	[Overview](#overview)
2.	[Interpretation](#interpretation)
3.	[Byte/Bytes](#bytebytes)
4.	[HTTP](#http)
5.	[Logger](#logger)
6.	[Logger::Level](#loggerlevel)
7.	[Request](#request)
8.	[Response](#response)
9.	[Resource](#resource)
10.	[Rule](#rule)
11.	[Service](#service)
12.	[SessionManager](#sessionmanager)
13.	[Session](#session)
14.	[Settings](#settings)
15.	[SSLSettings](#sslsettings)
16.	[StatusCode](#statuscode)
17.	[String](#string)
18.	[URI](#uri)
19.	[Further Reading](#further-reading)

### Byte/Bytes

```C++
typedef uint8_t Byte;

typedef std::vector< Byte > Bytes;
```

Byte represents an unsigned 8-bit wide data-type, Bytes provides container functionality with [Standard Template Library](http://en.cppreference.com/w/cpp) (STL) [vector](http://en.cppreference.com/w/cpp/container/vector) collection semantics.

See [std::uint8_t](http://en.cppreference.com/w/cpp/types/integer) and [std::vector](http://en.cppreference.com/w/cpp/container/vector) for further details.

### Http

The static HTTP class offers client capabilities for consuming RESTful services.

#### Methods

-	[to_bytes](#httpto_bytes)
-	[close](#httpclose)
-	[is_open](#httpis_open)
-	[is_closed](#httpis_closed)
-	[sync](#httpsync)
-	[async](#httpasync)
-	[fetch](#httpfetch)

#### Http::to_bytes

```C++
static Bytes to_bytes( const std::shared_ptr< Request >& value );

static Bytes to_bytes( const std::shared_ptr< Response >& value );
```

Convert a HTTP [request](#request)/[response](#response) object to a sequence of [bytes](#bytebytes).

##### Parameters

| parameter | type                           | default value | direction |
|:---------:|--------------------------------|:-------------:|:---------:|
|   value   | [restbed::Request](#request)   |      n/a      |   input   |
|   value   | [restbed::Response](#response) |      n/a      |   input   |

##### Return Value

Collection of [bytes](#bytebytes) representing the raw request representation.

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).

#### Http::close

```C++
static void close( const std::shared_ptr< Request >& value );
```

Shutdown an active HTTP [request](#request) object, causing its underlying socket to be disconnected. Invoking this method on a inactive [request](#request) has no effect.

##### Parameters

| parameter | type                         | default value | direction |
|:---------:|------------------------------|:-------------:|:---------:|
|   value   | [restbed::Request](#request) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).

#### Http::is_open

```C++
static bool is_open( const std::shared_ptr< Request >& value );
```

Determine if the HTTP [request](#request) object is active, that is say, it has a connected socket to a remote endpoint. Invoking this method on a inactive [request](#request) has no effect.

##### Parameters

| parameter | type                         | default value | direction |
|:---------:|------------------------------|:-------------:|:---------:|
|   value   | [restbed::Request](#request) |      n/a      |   input   |

##### Return Value

Boolean true if the underlying socket is connected, else false.

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).

#### Http::is_closed

```C++
static bool is_closed( const std::shared_ptr< Request >& value );
```

Determine if the HTTP [request](#request) object is inactive, that is say, it has a disconnected socket. Invoking this method on a inactive [request](#request) has no effect.

##### Parameters

| parameter | type                         | default value | direction |
|:---------:|------------------------------|:-------------:|:---------:|
|   value   | [restbed::Request](#request) |      n/a      |   input   |

##### Return Value

Boolean true if the underlying socket is disconnected, else false.

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).

#### Http::sync

```C++
static const std::shared_ptr< Response > sync( const std::shared_ptr< Request > request, const std::shared_ptr< const Settings >& settings = std::make_shared< Settings >( ) );
```

Perform a synchronous, read: wait for the result, HTTP [request](#request). If an error occurs the [response](#response) will contain details of the error, indicated by a status code of zero (0).

[Settings](#settings) may be specified via the second parameter.

##### Parameters

| parameter | type                           | default value | direction |
|:---------:|--------------------------------|:-------------:|:---------:|
|  request  | [restbed::Request](#request)   |      n/a      |   input   |
| settings  | [restbed::Settings](#settings) |      n/a      |   input   |

##### Return Value

The HTTP [response](#response) returned from the endpoint specified in the [request](#request) object, otherwise an error condition.

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).

#### Http::async

```C++
static std::future< std::shared_ptr< Response > > async( const std::shared_ptr< Request > request, const std::function< void ( const std::shared_ptr< Request >, const std::shared_ptr< Response > ) >& callback, const std::shared_ptr< const Settings >& settings = std::make_shared< Settings >( ) );
```

Perform an asynchronous, read: don't wait for the result, HTTP [request](#request). If an error occurs the [response](#response) will contain details of the error, indicated by a status code of zero (0).

The second callback parameter will be invoked when the service has finished responding to the [request](#request).

[Settings](#settings) may be specified via the third parameter.

##### Parameters

| parameter | type                                                                          | default value | direction |
|:---------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
|  request  | [restbed::Request](#request)                                                  |      n/a      |   input   |
| callback  | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |
| settings  | [restbed::Settings](#settings)                                                |      n/a      |   input   |

##### Return Value

[std::future](http://en.cppreference.com/w/cpp/thread/future) holding the pending [restbed::Response](#response).

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).

#### Http::async

```C++
static Bytes fetch( const std::size_t length, const std::shared_ptr< Response >& response );

static Bytes fetch( const std::string& delimiter, const std::shared_ptr< Response >& response );
```

Fetch the contents of a response body by either length or delimiter value.

##### Parameters

| parameter | type                                                                | default value | direction |
|:---------:|---------------------------------------------------------------------|:-------------:|:---------:|
| response  | [restbed::Response](#response)                                      |      n/a      |   input   |
|  length   | [std::size_t](http://en.cppreference.com/w/cpp/types/size_t)        |      n/a      |   input   |
| delimiter | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

Sequence of [restbed::Bytes](#bytebytes) representing a portion or a complete response body determined by length or delimiter parameter options.

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).

### Logger

Interface detailing the required contract for logger extensions.

No default logger is supplied with the codebase and it is the responsibility of third-party developers to implement the desired behaviour.

#### Methods

-	[start](#loggerstart)
-	[stop](#loggerstop)
-	[log](#loggerlog)
-	[log_if](#loggerlog_if)
-	[level](#loggerlevel)

#### Logger::start

```C++
virtual void start( const std::shared_ptr< const restbed::Settings >& settings ) = 0;
```

Initialise a logger instance; see also [stop](#loggerstop).

The [Settings](#settings) passed are the same as those given to [Exchange::start](#exchangestart).

After this method has returned the instance **MUST** be ready to start receiving [log](#loggerlog) and [log_if](#loggerlog_if) invocations.

##### Parameters

| name  | type                           | default value | direction |
|:-----:|--------------------------------|:-------------:|:---------:|
| value | [restbed::Settings](#settings) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

Any exceptions raised will result in the service failing to start.

#### Logger::stop

```C++
virtual void stop( void ) = 0;
```

Halt/Clean-up logger resources; see also [start](#loggerstart).

##### Parameters

n/a

##### Return Value

n/a

##### Exceptions

Exceptions raised will result in a dirty service teardown.

#### Logger::log

```C++
virtual void log( const Level level, const char* format, ... ) = 0;
```

Commit the message specified under the control of a format string, with the specified level of severity into the log; see also [log_if](#loggerlog_if).

See [printf](http://en.cppreference.com/w/cpp/io/c/fprintf) family of functions for format directives.

> The format string is composed of zero or more directives: ordinary characters (not %), which are copied unchanged to the output stream; and conversion specifications, each of which results in fetching zero or more subsequent arguments. Each conversion specification is >introduced by the % character.

##### Parameters

| name   | type                                                                        | default value | direction |
|:------:|-----------------------------------------------------------------------------|:-------------:|:---------:|
| level  | [restbed::Logger::Level](#loggerlevel)                                      |      n/a      |   input   |
| format | [char\*](http://en.cppreference.com/w/cpp/language/types)                   |      n/a      |   input   |
|  ...   | [variadic argument list](http://en.cppreference.com/w/cpp/utility/variadic) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

Any exceptions raised will result in the service ignoring the fault and printing directly to [Standard Error (stderr)](http://en.cppreference.com/w/cpp/io/c).

#### Logger::log_if

```C++
virtual void log_if( bool expression, const Level level, const char* format, ... ) = 0;
```

Commit the message specified under the control of a format string, with the specified level of severity into the log, under the condition that expression is equal to boolean true; see also [log](#loggerlog).

##### Parameters

| parameter   | type                                                                        | default value | direction |
|:-----------:|-----------------------------------------------------------------------------|:-------------:|:---------:|
| expresssion | [bool](http://en.cppreference.com/w/cpp/language/types)                     |      n/a      |   input   |
|    level    | [restbed::Logger::Level](#loggerlevel)                                      |      n/a      |   input   |
|   format    | [char\*](http://en.cppreference.com/w/cpp/language/types)                   |      n/a      |   input   |
|     ...     | [variadic argument list](http://en.cppreference.com/w/cpp/utility/variadic) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

Any exceptions raised will result in the service ignoring the fault and printing directly to [Standard Error (stderr)](http://en.cppreference.com/w/cpp/io/c).

#### Logger::Level

```C++
class Logger
{
    enum Level : int
    {
        INFO = 0000,
        DEBUG = 1000,
        FATAL = 2000,
        ERROR = 3000,
        WARNING = 4000,
        SECURITY = 5000
    };
}
```

[Enumeration](http://en.cppreference.com/w/cpp/language/enum) used in conjunction with the [Logger interface](#logger) to detail the level of severity towards a particular log entry.

### Request

Represents a HTTP request with additional helper methods for manipulating data, and improving code readability.

#### Methods

-	[constructor](#requestconstructor)
-	[destructor](#requestdestructor)
-	[has_header](#requesthas_header)
-	[has_path_parameter](#requesthas_path_parameter)
-	[has_query_parameter](#requesthas_query_parameter)
-	[get_port](#requestget_port)
-	[get_version](#requestget_version)
-	[get_body](#requestget_body)
-	[get_response](#requestget_response)
-	[get_host](#requestget_host)
-	[get_path](#requestget_path)
-	[get_method](#requestget_method)
-	[get_protocol](#requestget_protocol)
-	[get_header](#requestget_header)
-	[get_headers](#requestget_headers)
-	[get_query_parameter](#requestget_query_parameter)
-	[get_query_parameters](#requestget_query_parameters)
-	[get_path_parameter](#requestget_path_parameter)
-	[get_path_parameters](#requestget_path_parameters)
-	[set_body](#requestset_body)
-	[set_port](#requestset_port)
-	[set_version](#requestset_version)
-	[set_path](#requestset_path)
-	[set_host](#requestset_host)
-	[set_method](#requestset_method)
-	[set_protocol](#requestset_protocol)
-	[set_header](#requestset_header)
-	[set_headers](#requestset_headers)
-	[set_query_parameter](#requestset_query_parameter)
-	[set_query_parameters](#requestset_query_parameters)

#### Request::constructor

```C++
Request( void );
Request( const Uri& value );
```

Initialises a new class instance, if a [Uri](#uri) is supplied it will be used to override the default class property values; see also [destructor](#requestdestructor).

##### Parameters

| name  | type        | default value | direction |
|:-----:|-------------|:-------------:|:---------:|
| value | [Uri](#uri) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Request::destructor

```C++
virtual ~Request( void );
```

Clean-up class instance; see also [constructor](#requestconstructor).

##### Parameters

n/a

##### Return Value

n/a

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).

#### Request::has_header

```C++
bool has_header( const std::string& name ) const;
```

Case insensitive check to confirm if the [request](#request) contains a header with the supplied name.

##### Parameters

| name | type                                                                | default value | direction |
|:----:|---------------------------------------------------------------------|:-------------:|:---------:|
| name | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

Boolean true if the [request](#request) holds a header with a matching name, else false.

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).

#### Request::has_path_parameter

```C++
bool has_path_parameter( const std::string& name ) const;
```

Case insensitive check to confirm if the [request](#request) contains a path parameter with the supplied name.

##### Parameters

| name | type                                                                | default value | direction |
|:----:|---------------------------------------------------------------------|:-------------:|:---------:|
| name | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

Boolean true if the [request](#request) holds a path parameter with a matching name, else false.

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).

#### Request::has_query_parameter

```C++
bool has_query_parameter( const std::string& name ) const;
```

Case insensitive check to confirm if the [request](#request) contains a query parameter with the supplied name.

##### Parameters

| name | type                                                                | default value | direction |
|:----:|---------------------------------------------------------------------|:-------------:|:---------:|
| name | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

Boolean true if the [request](#request) holds a query parameter with a matching name, else false.

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).

#### Request::get_port

```C++
uint16_t get_port( void ) const;
```

Retrieves the port number of the endpoint; see also [set_port](#requestset_port).

##### Parameters

n/a

##### Return Value

[uint16_t](http://en.cppreference.com/w/cpp/types/integer) representing the port number.

##### Exceptions

n/a

#### Request::get_version

```C++
double get_version( void ) const;
```

Retrieves the [HTTP version](https://tools.ietf.org/html/rfc2145) number; see also [set_version](#requestset_version).

##### Parameters

n/a

##### Return Value

[double](http://en.cppreference.com/w/cpp/language/types%23Floating_point_types) representing the [HTTP version](https://tools.ietf.org/html/rfc2145).

##### Exceptions

n/a

#### Request::get_body

```C++
Bytes get_body( void ) const;

void get_body( std::string& body, const std::function< std::string ( const Bytes& ) >& transform = nullptr ) const;
```

1) Retrieves the contents of the request body; see also [set_body](#requestset_body).

2) Alters the request body with the transform operation and returns the result as a [std::string](http://en.cppreference.com/w/cpp/string/basic_string); see also [set_body](#requestset_body).

##### Parameters

| name      | type                                                                          | default value | direction |
|:---------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
|   body    | [std::string](http://en.cppreference.com/w/cpp/string/basic_string)           |      n/a      |  output   |
| transform | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

[Bytes](#bytebytes) representing the request body.

##### Exceptions

n/a

const std::shared_ptr< const Response > get_response( void ) const;

std::string get_host( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;

std::string get_path( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;

std::string get_method( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;

std::string get_protocol( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;

void get_header( const std::string& name, int& value, const int default_value = 0 ) const;

void get_header( const std::string& name, long& value, const long default_value = 0 ) const;

void get_header( const std::string& name, float& value, const float default_value = 0 ) const;

void get_header( const std::string& name, double& value, const double default_value = 0 ) const;

void get_header( const std::string& name, long long& value, const long long default_value = 0 ) const;

void get_header( const std::string& name, unsigned int& value, const unsigned int default_value = 0 ) const;

void get_header( const std::string& name, unsigned long& value, const unsigned long default_value = 0 ) const;

void get_header( const std::string& name, unsigned long long& value, const unsigned long long default_value = 0 ) const;

std::multimap< std::string, std::string > get_headers( const std::string& name = "" ) const;

std::string get_header( const std::string& name, const std::string& default_value = "" ) const;

std::string get_header( const std::string& name, const std::function< std::string ( const std::string& ) >& transform ) const;

void get_query_parameter( const std::string& name, int& value, const int default_value = 0 ) const;

void get_query_parameter( const std::string& name, long& value, const long default_value = 0 ) const;

void get_query_parameter( const std::string& name, float& value, const float default_value = 0 ) const;

void get_query_parameter( const std::string& name, double& value, const double default_value = 0 ) const;

void get_query_parameter( const std::string& name, long long& value, const long long default_value = 0 ) const;

void get_query_parameter( const std::string& name, unsigned int& value, const unsigned int default_value = 0 ) const;

void get_query_parameter( const std::string& name, unsigned long& value, const unsigned long default_value = 0 ) const;

void get_query_parameter( const std::string& name, unsigned long long& value, const unsigned long long default_value = 0 ) const;

std::string get_query_parameter( const std::string& name, const String::Option option = String::CASE_INSENSITIVE ) const;

std::string get_query_parameter( const std::string& name, const std::string& default_value, const String::Option option = String::CASE_INSENSITIVE ) const;

std::string get_query_parameter( const std::string& name, const std::function< std::string ( const std::string& ) >& transform, const String::Option option = String::CASE_INSENSITIVE ) const;

std::multimap< std::string, std::string > get_query_parameters( const std::string& name = "", const String::Option option = String::CASE_INSENSITIVE ) const;

void get_path_parameter( const std::string& name, int& value, const int default_value = 0 ) const;

void get_path_parameter( const std::string& name, long& value, const long default_value = 0 ) const;

void get_path_parameter( const std::string& name, float& value, const float default_value = 0 ) const;

void get_path_parameter( const std::string& name, double& value, const double default_value = 0 ) const;

void get_path_parameter( const std::string& name, long long& value, const long long default_value = 0 ) const;

void get_path_parameter( const std::string& name, unsigned int& value, const unsigned int default_value = 0 ) const;

void get_path_parameter( const std::string& name, unsigned long& value, const unsigned long default_value = 0 ) const;

void get_path_parameter( const std::string& name, unsigned long long& value, const unsigned long long default_value = 0 ) const;

std::string get_path_parameter( const std::string& name, const String::Option option = String::CASE_INSENSITIVE ) const;

std::string get_path_parameter( const std::string& name, const std::string& default_value, const String::Option option = String::CASE_INSENSITIVE ) const;

std::string get_path_parameter( const std::string& name, const std::function< std::string ( const std::string& ) >& transform, const String::Option option = String::CASE_INSENSITIVE ) const;

std::map< std::string, std::string > get_path_parameters( const std::string& name = "", const String::Option option = String::CASE_INSENSITIVE ) const;

void set_body( const Bytes& value );

void set_body( const std::string& value );

void set_port( const uint16_t value );

void set_version( const double value );

void set_path( const std::string& value );

void set_host( const std::string& value );

void set_method( const std::string& value );

void set_protocol( const std::string& value );

void set_header( const std::string& name, const std::string& value );

void set_headers( const std::multimap< std::string, std::string >& values );

void set_query_parameter( const std::string& name, const std::string& value );

void set_query_parameters( const std::multimap< std::string, std::string >& values );

### Response

Represents a HTTP response with additional helper methods for manipulating data, and improving code readability.

See [restbed::Response](https://github.com/corvusoft/restbed/documentation/API.md#response) for further details.

### Further Reading

[C++ Standard](https://isocpp.org/std/the-standard) - The current ISO C++ standard is officially known as ISO International Standard ISO/IEC 14882:2014(E) – Programming Language C++. Want to read the ISO C++ standard, or working drafts of the standard? You have several options, most of them free.

[C++ Reference](http://en.cppreference.com/) - Comprehensive C++ and Standard Template Library (STL) reference.

[Effective STL](https://www.amazon.com/Effective-STL-Specific-Standard-Template/dp/0201749629) - Written for the intermediate or advanced C++ programmer, renowned C++ expert Scott Meyers provides essential techniques for getting more out of the Standard Template Library in Effective STL, a tutorial for doing more with this powerful library.

[Effective C++](https://www.amazon.com/Effective-Specific-Improve-Programs-Designs/dp/0321334876) - “Every C++ professional needs a copy of Effective C++. It is an absolute must-read for anyone thinking of doing serious C++ development. If you’ve never read Effective C++ and you think you know everything about C++, think again.” — Steve Schirripa, Software Engineer, Google
