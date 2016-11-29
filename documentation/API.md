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
12.	[Session](#session)
13.	[SessionManager](#sessionmanager)
14.	[Settings](#settings)
15.	[SSLSettings](#sslsettings)
16.	[StatusCode](#statuscode)
17.	[String](#string)
18.	[String::Option](#stringoption)
19.	[URI](#uri)
20.	[WebSocket](#websocket)
21.	[WebSocketMessage](#websocketmessage)
22.	[Further Reading](#further-reading)

### Byte/Bytes

```C++
typedef uint8_t Byte;

typedef std::vector< Byte > Bytes;
```

Byte represents an unsigned 8-bit wide data-type, Bytes provides container functionality with [Standard Template Library](http://en.cppreference.com/w/cpp) (STL) [vector](http://en.cppreference.com/w/cpp/container/vector) collection semantics.

See [std::uint8_t](http://en.cppreference.com/w/cpp/types/integer) and [std::vector](http://en.cppreference.com/w/cpp/container/vector) for further details.

### Http

The static HTTP class offers limited client capabilities for consuming RESTful services. This will be removed in future version and replaced with the Restless client framework.

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

#### Http::fetch

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

Commit the message specified under the control of a format string, with the specified level of severity into the log, under the condition that the expression is equal to boolean true; see also [log](#loggerlog).

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
-	[add_header](#requestadd_header)
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

Retrieves the network port number of the server endpoint; see also [set_port](#requestset_port).

##### Parameters

n/a

##### Return Value

[uint16_t](http://en.cppreference.com/w/cpp/types/integer) representing the network port number.

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

1) Retrieves the contents of the request body as [Bytes](#bytebytes); see also [set_body](#requestset_body).

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

#### Request::get_response

```C++
const std::shared_ptr< const Response > get_response( void ) const;
```

Retrieves the associated HTTP [response](#response) for this request, if any.

##### Parameters

n/a

##### Return Value

[std::shared_ptr](http://en.cppreference.com/w/cpp/memory/shared_ptr) representing the response, else nullptr.

##### Exceptions

n/a

#### Request::get_host

```C++
std::string get_host( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
```

Retrieves the a host for this request, optionally applying a text transformation.

##### Parameters

| name      | type                                                                          | default value | direction |
|:---------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| transform | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

[std::string](http://en.cppreference.com/w/cpp/string/basic_string) representing the host.

##### Exceptions

n/a

#### Request::get_path

```C++
std::string get_path( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
```

Retrieves the path for this request, optionally applying a text transformation.

##### Parameters

| name      | type                                                                          | default value | direction |
|:---------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| transform | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

[std::string](http://en.cppreference.com/w/cpp/string/basic_string) representing the path.

##### Exceptions

n/a

#### Request::get_method

```C++
std::string get_method( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
```

Retrieves the [HTTP method](https://www.w3.org/Protocols/rfc2616/rfc2616-sec9.html) for this request, optionally applying a text transformation.

##### Parameters

| name      | type                                                                          | default value | direction |
|:---------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| transform | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

[std::string](http://en.cppreference.com/w/cpp/string/basic_string) representing the [HTTP method](https://www.w3.org/Protocols/rfc2616/rfc2616-sec9.html).

##### Exceptions

n/a

#### Request::get_protocol

```C++
std::string get_protocol( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
```

Retrieves the protocol for this request, optionally applying a text transformation.

##### Parameters

| name      | type                                                                          | default value | direction |
|:---------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| transform | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

[std::string](http://en.cppreference.com/w/cpp/string/basic_string) representing the protocol.

##### Exceptions

n/a

#### Request::get_header

```C++
template< typename Type, typename std::enable_if< std::is_arithmetic< Type >::value, Type >::type = 0 >
Type get_header( const std::string& name, const Type default_value ) const

std::string get_header( const std::string& name, const std::string& default_value ) const;

std::string get_header( const std::string& name, const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
```

1) Retrieve the first header with a matching name parsing to a an arithmetic value. if not found return default_value.

2) Retrieve the first header with a matching name as a [std::string](http://en.cppreference.com/w/cpp/string/basic_string). if not found return default_value.

3) Retrieve the first header with a matching name as a [std::string](http://en.cppreference.com/w/cpp/string/basic_string), optionally applying a transformation.

##### Parameters

| name          | type                                                                              | default value | direction |
|:-------------:|-----------------------------------------------------------------------------------|:-------------:|:---------:|
| transform     | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function)     |      n/a      |   input   |
| default_value | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) or arithmetic |      n/a      |   input   |

##### Return Value

[std::string](http://en.cppreference.com/w/cpp/string/basic_string) or arithmetic value representing the header.

##### Exceptions

n/a

#### Request::get_headers

```C++
std::multimap< std::string, std::string > get_headers( const std::string& name = "" ) const;
```

Retrieves all headers as a [std::multimap](http://en.cppreference.com/w/cpp/container/multimap). if a name is supplied only matching headers will be returned.

##### Parameters

| name      | type                                                                          | default value | direction |
|:---------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| transform | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

[std::multimap](http://en.cppreference.com/w/cpp/container/multimap) representing a collection of headers.

##### Exceptions

n/a

#### Request::get_query_parameter

```C++
template< typename Type, typename std::enable_if< std::is_arithmetic< Type >::value, Type >::type = 0 >
Type get_query_parameter( const std::string& name, const Type default_value ) const

std::string get_query_parameter( const std::string& name, const std::string& default_value ) const;

std::string get_query_parameter( const std::string& name, const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
```

1) Retrieve the first query parameter with a matching name parsing to a an arithmetic value. if not found return default_value.

2) Retrieve the first query parameter with a matching name as a [std::string](http://en.cppreference.com/w/cpp/string/basic_string). if not found return default_value.

3) Retrieve the first query parameter with a matching name as a [std::string](http://en.cppreference.com/w/cpp/string/basic_string), optionally applying a transformation.

##### Parameters

| name          | type                                                                              | default value | direction |
|:-------------:|-----------------------------------------------------------------------------------|:-------------:|:---------:|
| transform     | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function)     |      n/a      |   input   |
| default_value | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) or arithmetic |      n/a      |   input   |

##### Return Value

[std::string](http://en.cppreference.com/w/cpp/string/basic_string) or arithmetic value representing the query parameter.

##### Exceptions

n/a

#### Request::get_query_parameters

```C++
std::multimap< std::string, std::string > get_query_parameters( const std::string& name = "", const String::Option option = String::CASE_INSENSITIVE ) const;
```

Retrieves all query parameters as a [std::multimap](http://en.cppreference.com/w/cpp/container/multimap). if a name is supplied only matching parameters will be returned.

##### Parameters

| name      | type                                                                          | default value | direction |
|:---------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| transform | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |
| option    | [String::Option](#stringoption)                                               |      n/a      |   input   |

##### Return Value

[std::multimap](http://en.cppreference.com/w/cpp/container/multimap) representing a collection of parameters.

##### Exceptions

n/a

#### Request::get_path_parameter

```C++
template< typename Type, typename std::enable_if< std::is_arithmetic< Type >::value, Type >::type = 0 >
Type get_path_parameter( const std::string& name, const Type default_value ) const

std::string get_path_parameter( const std::string& name, const std::string& default_value ) const;

std::string get_path_parameter( const std::string& name, const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
```

1) Retrieve the first parameter with a matching name parsing to a an arithmetic value. if not found return default_value.

2) Retrieve the first parameter with a matching name as a [std::string](http://en.cppreference.com/w/cpp/string/basic_string). if not found return default_value.

3) Retrieve the first parameter with a matching name as a [std::string](http://en.cppreference.com/w/cpp/string/basic_string), optionally applying a transformation.

##### Parameters

| name          | type                                                                              | default value | direction |
|:-------------:|-----------------------------------------------------------------------------------|:-------------:|:---------:|
| transform     | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function)     |      n/a      |   input   |
| default_value | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) or arithmetic |      n/a      |   input   |

##### Return Value

[std::string](http://en.cppreference.com/w/cpp/string/basic_string) or arithmetic value representing the path parameter.

##### Exceptions

n/a

#### Request::get_path_parameters

```C++
std::map< std::string, std::string > get_path_parameters( const std::string& name = "", const String::Option option = String::CASE_INSENSITIVE ) const;
```

Retrieves all query parameters as a [std::multimap](http://en.cppreference.com/w/cpp/container/multimap). if a name is supplied only matching parameters will be returned.

##### Parameters

| name      | type                                                                          | default value | direction |
|:---------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| transform | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |
| option    | [String::Option](#stringoption)                                               |      n/a      |   input   |

##### Return Value

[std::multimap](http://en.cppreference.com/w/cpp/container/multimap) representing a collection of parameters.

##### Exceptions

n/a

#### Request::set_body

```C++
void set_body( const Bytes& value );

void set_body( const std::string& value );
```

Replace request body; see also [get_body](#requestget_body).

##### Parameters

| name  | type                                                                                       | default value | direction |
|:-----:|--------------------------------------------------------------------------------------------|:-------------:|:---------:|
| value | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) or [Bytes](#bytebytes) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Request::set_port

```C++
void set_port( const uint16_t value );
```

Replace request network port; see also [get_port](#requestget_port).

##### Parameters

| name  | type                                                            | default value | direction |
|:-----:|-----------------------------------------------------------------|:-------------:|:---------:|
| value | [std::uint16_t](http://en.cppreference.com/w/cpp/types/integer) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Request::set_version

```C++
void set_version( const double value );
```

Replace request version; see also [get_version](#requestget_version).

##### Parameters

| name  | type                                                                              | default value | direction |
|:-----:|-----------------------------------------------------------------------------------|:-------------:|:---------:|
| value | [double](hhttp://en.cppreference.com/w/cpp/language/types%23Floating_point_types) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Request::set_path

```C++
void set_path( const std::string& value );
```

Replace request path; see also [get_path](#requestget_path).

##### Parameters

| name  | type                                                                | default value | direction |
|:-----:|---------------------------------------------------------------------|:-------------:|:---------:|
| value | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Request::set_host

```C++
void set_host( const std::string& value );
```

Replace request host; see also [get_host](#requestget_host).

##### Parameters

| name  | type                                                                | default value | direction |
|:-----:|---------------------------------------------------------------------|:-------------:|:---------:|
| value | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Request::set_method

```C++
void set_method( const std::string& value );
```

Replace request method; see also [get_method](#requestget_method).

##### Parameters

| name  | type                                                                | default value | direction |
|:-----:|---------------------------------------------------------------------|:-------------:|:---------:|
| value | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Request::set_protocol

```C++
void set_protocol( const std::string& value );
```

Replace request protocol; see also [get_protocol](#requestget_protocol).

##### Parameters

| name  | type                                                                | default value | direction |
|:-----:|---------------------------------------------------------------------|:-------------:|:---------:|
| value | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Request::add_header

```C++
void add_header( const std::string& name, const std::string& value );
```

Add a HTTP header to the request, existing headers that share the same name will not be altered.

##### Parameters

| name  | type                                                                | default value | direction |
|:-----:|---------------------------------------------------------------------|:-------------:|:---------:|
| name  | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |
| value | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Request::set_header

```C++
void set_header( const std::string& name, const std::string& value );
```

Set a HTTP header, existing headers that share the same name will be erased.

##### Parameters

| name  | type                                                                | default value | direction |
|:-----:|---------------------------------------------------------------------|:-------------:|:---------:|
| name  | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |
| value | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Request::set_headers

```C++
void set_header( const std::string& name, const std::string& value );
```

Set HTTP headers, existing headers will be erased.

##### Parameters

| name   | type                                                                 | default value | direction |
|:------:|----------------------------------------------------------------------|:-------------:|:---------:|
| values | [std::multimap](http://en.cppreference.com/w/cpp/container/multimap) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Request::set_query_parameter

```C++
void set_query_parameter( const std::string& name, const std::string& value );
```

Set a HTTP query parameter, existing parameters that share the same name will be erased.

##### Parameters

| name  | type                                                                | default value | direction |
|:-----:|---------------------------------------------------------------------|:-------------:|:---------:|
| name  | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |
| value | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Request::set_query_parameters

```C++
void set_query_parameters( const std::multimap< std::string, std::string >& values );
```

Set HTTP query parameters, existing parameters will be erased.

##### Parameters

| name   | type                                                                 | default value | direction |
|:------:|----------------------------------------------------------------------|:-------------:|:---------:|
| values | [std::multimap](http://en.cppreference.com/w/cpp/container/multimap) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

### Response

Represents a HTTP response with additional helper methods for manipulating data, and improving code readability.

#### Methods

-	[constructor](#responseconstructor)
-	[destructor](#responsedestructor)
-	[has_header](#responsehas_header)
-	[get_body](#responseget_body)
-	[get_version](#responseget_host)
-	[get_status_code](#responseget_path)
-	[get_protocol](#responseget_method)
-	[get_status_message](#responseget_protocol)
-	[get_header](#responseget_header)
-	[get_headers](#responseget_headers)
-	[set_body](#responseset_body)
-	[set_version](#responseset_version)
-	[set_status_code](#responseset_path)
-	[set_protocol](#responseset_host)
-	[set_status_message](#responseset_method)
-	[add_header](#responseadd_header)
-	[set_header](#responseset_header)
-	[set_headers](#responseset_headers)

#### Response::constructor

```C++
Response( void );
```

Initialises a new class instance; see also [destructor](#responsedestructor).

##### Parameters

n/a

##### Return Value

n/a

##### Exceptions

n/a

#### Response::destructor

```C++
virtual ~Response( void );
```

Clean-up class instance; see also [constructor](#responseconstructor).

##### Parameters

n/a

##### Return Value

n/a

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).

#### Response::has_header

```C++
bool has_header( const std::string& name ) const;
```

Case insensitive check to confirm if the [response](#response) contains a header with the supplied name.

##### Parameters

| name | type                                                                | default value | direction |
|:----:|---------------------------------------------------------------------|:-------------:|:---------:|
| name | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

Boolean true if the [response](#response) holds a header with a matching name, else false.

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).

#### Response::get_body

```C++
Bytes get_body( void ) const;

void get_body( std::string& body, const std::function< std::string ( const Bytes& ) >& transform = nullptr ) const;
```

1) Retrieves the contents of the response body as [Bytes](#bytebytes); see also [set_body](#responseset_body).

2) Alters the response body with the transform operation and returns the result as a [std::string](http://en.cppreference.com/w/cpp/string/basic_string); see also [set_body](#responseset_body).

##### Parameters

| name      | type                                                                          | default value | direction |
|:---------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
|   body    | [std::string](http://en.cppreference.com/w/cpp/string/basic_string)           |      n/a      |  output   |
| transform | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

[Bytes](#bytebytes) representing the response body.

##### Exceptions

n/a

#### Response::get_version

```C++
double get_version( void ) const;
```

Retrieves the [HTTP version](https://tools.ietf.org/html/rfc2145) number; see also [set_version](#responseset_version).

##### Parameters

n/a

##### Return Value

[double](http://en.cppreference.com/w/cpp/language/types%23Floating_point_types) representing the [HTTP version](https://tools.ietf.org/html/rfc2145).

##### Exceptions

n/a

#### Response::get_status_code

```C++
int get_status_code( void ) const;
```

Retrieves the [HTTP status code](https://tools.ietf.org/html/rfc7231#section-6.1); see also [set_status_code](#responseset_status_code).

##### Parameters

n/a

##### Return Value

Integer representing the [HTTP status code](https://tools.ietf.org/html/rfc7231#section-6.1).

##### Exceptions

n/a

#### Response::get_protocol

```C++
std::string get_protocol( void ) const;
```

Retrieve the protocol.

##### Parameters

n/a

##### Return Value

[std::string](http://en.cppreference.com/w/cpp/string/basic_string) representing the protocol.

##### Exceptions

n/a

#### Response::get_status_message

```C++
std::string get_status_message( void ) const;
```

Retrieves the [HTTP status message](https://tools.ietf.org/html/rfc7231#section-6.1); see also [set_status_message](#responseset_status_message).

##### Parameters

n/a

##### Return Value

[std::string](http://en.cppreference.com/w/cpp/string/basic_string) representing the [HTTP status message](https://tools.ietf.org/html/rfc7231#section-6.1).

##### Exceptions

n/a

#### Response::get_header

```C++
template< typename Type, typename std::enable_if< std::is_arithmetic< Type >::value, Type >::type = 0 >
Type get_header( const std::string& name, const Type default_value ) const

std::string get_header( const std::string& name, const std::string& default_value ) const;

std::string get_header( const std::string& name, const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
```

1) Retrieve the first header with a matching name parsing to a an arithmetic value. if not found return default_value.

2) Retrieve the first header with a matching name as a [std::string](http://en.cppreference.com/w/cpp/string/basic_string). if not found return default_value.

3) Retrieve the first header with a matching name as a [std::string](http://en.cppreference.com/w/cpp/string/basic_string), optionally applying a transformation.

##### Parameters

| name          | type                                                                              | default value | direction |
|:-------------:|-----------------------------------------------------------------------------------|:-------------:|:---------:|
| transform     | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function)     |      n/a      |   input   |
| default_value | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) or arithmetic |      n/a      |   input   |

##### Return Value

[std::string](http://en.cppreference.com/w/cpp/string/basic_string) or arithmetic value representing the header.

##### Exceptions

n/a

#### Response::get_headers

```C++
std::multimap< std::string, std::string > get_headers( const std::string& name = "" ) const;
```

Retrieves all headers as a [std::multimap](http://en.cppreference.com/w/cpp/container/multimap). if a name is supplied only matching headers will be returned.

##### Parameters

| name      | type                                                                          | default value | direction |
|:---------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| transform | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

[std::multimap](http://en.cppreference.com/w/cpp/container/multimap) representing a collection of headers.

##### Exceptions

n/a

#### Response::set_body

```C++
void set_body( const Bytes& value );

void set_body( const std::string& value );
```

Replace response body; see also [get_body](#responseget_body).

##### Parameters

| name  | type                                                                                       | default value | direction |
|:-----:|--------------------------------------------------------------------------------------------|:-------------:|:---------:|
| value | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) or [Bytes](#bytebytes) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Response::set_version

```C++
void set_version( const double value );
```

Replace response version; see also [get_version](#responseget_version).

##### Parameters

| name  | type                                                                              | default value | direction |
|:-----:|-----------------------------------------------------------------------------------|:-------------:|:---------:|
| value | [double](hhttp://en.cppreference.com/w/cpp/language/types%23Floating_point_types) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Response::set_status_code

```C++
void set_status_code( const int value );
```

Replace response status code; see also [get_status_code](#responseget_status_code).

##### Parameters

| name  | type                                                                | default value | direction |
|:-----:|----------------------------------------------------------------------|:-------------:|:---------:|
| value | [int](http://en.cppreference.com/w/cpp/types/integer) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Response::set_protocol

```C++
void set_protocol( const std::string& value );
```

Replace response protocol; see also [get_protocol](#responseget_protocol).

##### Parameters

| name  | type                                                                | default value | direction |
|:-----:|---------------------------------------------------------------------|:-------------:|:---------:|
| value | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Response::set_status_message

```C++
void set_status_message( const std::string& value );
```

Replace response status message; see also [get_status_message](#responseget_status_message).

##### Parameters

| name  | type                                                                | default value | direction |
|:-----:|---------------------------------------------------------------------|:-------------:|:---------:|
| value | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Response::add_header

```C++
void add_header( const std::string& name, const std::string& value );
```

Add a HTTP header to the response, existing headers that share the same name will not be altered.

##### Parameters

| name  | type                                                                | default value | direction |
|:-----:|---------------------------------------------------------------------|:-------------:|:---------:|
| name  | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |
| value | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Response::set_header

```C++
void set_header( const std::string& name, const std::string& value );
```

Set a HTTP header, existing headers that share the same name will be erased; see also [get_header](#responseget_header).

##### Parameters

| name  | type                                                                | default value | direction |
|:-----:|---------------------------------------------------------------------|:-------------:|:---------:|
| name  | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |
| value | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Response::set_headers

```C++
void set_headers( const std::multimap< std::string, std::string >& values );
```

Set HTTP headers, existing headers will be erased; see also [get_headers](#responseget_headers).

##### Parameters

| name   | type                                                                 | default value | direction |
|:------:|----------------------------------------------------------------------|:-------------:|:---------:|
| values | [std::multimap](http://en.cppreference.com/w/cpp/container/multimap) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

### Resource

Resource represents an network communication endpoint. This is the primary data-structure used throughout to represent RESTful resources. All resource specific filteration, request processing rules, and authentication must be placed on this entity.

#### Methods

-	[constructor](#resourceconstructor)
-	[destructor](#resourcedestructor)
-	[add_rule](#resourceadd_rule)
-	[set_path](#resourceset_path)
-	[set_paths](#resourceset_paths)
-	[set_default_header](#resourceset_default_header)
-	[set_default_headers](#resourceset_default_headers)
-	[set_failed_filter_validation_handler](#resourceset_failed_filter_validation_handler)
-	[set_error_handler](#resourceset_error_handler)
-	[set_authentication_handler](#resourceset_authentication_handler)
-	[set_method_handler](#resourceset_method_handler)

#### Resource::constructor

```C++
Resource( void );
```

Initialises a new class instance; see also [destructor](#resourcedestructor).

##### Parameters

n/a

##### Return Value

n/a

##### Exceptions

n/a

#### Resource::destructor

```C++
virtual ~Resource( void );
```

Clean-up class instance; see also [constructor](#resourceconstructor).

##### Parameters

n/a

##### Return Value

n/a

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).

#### Resource::add_rule

```C++
void add_rule( const std::shared_ptr< Rule >& rule );

void add_rule( const std::shared_ptr< Rule >& rule, const int priority );
```

Add incoming request processing rule; see also [Rule](#rule).

##### Parameters

| name       | type                                                  | default value | direction |
|:----------:|-------------------------------------------------------|:-------------:|:---------:|
| rule       | [Rule](#rule)                                         |      n/a      |   input   |
| priority   | [int](http://en.cppreference.com/w/cpp/types/integer) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Resource::set_path

```C++
void set_path( const std::string& value );
```

Set the path with which this resource should be accessible. [Settings::set_root](settingsset_root) will be perpended to this value.

##### Parameters

| name       | type                                                                | default value | direction |
|:----------:|---------------------------------------------------------------------|:-------------:|:---------:|
| value      | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Resource::set_paths

```C++
void set_paths( const std::set< std::string >& values );
```

Set the paths with which this resource should be accessible. [Settings::set_root](settingsset_root) will be perpended to all values.

##### Parameters

| name       | type                                                                | default value | direction |
|:----------:|---------------------------------------------------------------------|:-------------:|:---------:|
| values     | [std::set](http://en.cppreference.com/w/cpp/container/set)          |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Resource::set_default_header

```C++
void set_default_header( const std::string& name, const std::string& value );
```

Set a default header that should be sent on every HTTP response, overriding any existing value with the same name.

##### Parameters

| name       | type                                                                | default value | direction |
|:----------:|---------------------------------------------------------------------|:-------------:|:---------:|
| name       | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |
| value      | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Resource::set_default_headers

```C++
void set_default_headers( const std::multimap< std::string, std::string >& values );
```

Set default headers that should be sent on every HTTP response, overriding any existing values.

##### Parameters

| name       | type                                                                 | default value | direction |
|:----------:|----------------------------------------------------------------------|:-------------:|:---------:|
| name       | [std::multimap](http://en.cppreference.com/w/cpp/container/multimap) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Resource::set_failed_filter_validation_handler

```C++
void set_failed_filter_validation_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value );
```

Set failed filter validation handler. If an incoming request fails to match the resources filters this method will be invoked offering an opportunity to return a custom HTTP response.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| value      | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Resource::set_error_handler

```C++
void set_error_handler( const std::function< void ( const int, const std::exception&, const std::shared_ptr< Session > ) >& value );
```

Set error handler. If during processing a failure occurs this method will be invoked for reporting and HTTP response handling.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| value      | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Resource::set_authentication_handler

```C++
void set_authentication_handler( const std::function< void ( const std::shared_ptr< Session >, const std::function< void ( const std::shared_ptr< Session > ) >& ) >& value );
```

Set authentication handler, this method will be invoked after the service authentication handler.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| value      | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Resource::set_method_handler

```C++
void set_method_handler( const std::string& method, const std::function< void ( const std::shared_ptr< Session > ) >& callback );

void set_method_handler( const std::string& method, const std::multimap< std::string, std::string >& filters, const std::function< void ( const std::shared_ptr< Session > ) >& callback );
```

Set method handler with optional header filters.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| method     | [std::string](http://en.cppreference.com/w/cpp/string/basic_string)           |      n/a      |   input   |
| filters    | [std::multimap](http://en.cppreference.com/w/cpp/container/multimap)          |      n/a      |   input   |
| callback   | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

### Rule

Interface representing an incoming processing rule.

#### Methods

-	[condition](#rulecondition)
-	[action](#ruleaction)
-	[get_priority](#ruleget_priority)
-	[set_priority](#ruleset_priority)

#### Rule::condition

```C++
virtual bool condition( const std::shared_ptr< Session > session );
```

The condition that decides if this rules action should be invoked; see also [action](#ruleaction).

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| session    | [std::shared_ptr](http://en.cppreference.com/w/cpp/memory/shared_ptr)         |      n/a      |   input   |

##### Return Value

True if the condition has been satisfied.

##### Exceptions

n/a

#### Rule::action

```C++
virtual void action( const std::shared_ptr< Session > session, const std::function< void ( const std::shared_ptr< Session > ) >& callback ) = 0;
```

The action to be invoked if the rules condition returns true; see also [condition](#rulecondition).

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| session    | [std::shared_ptr](http://en.cppreference.com/w/cpp/memory/shared_ptr)         |      n/a      |   input   |
| callback   | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Rule::get_priority

```C++
int get_priority( void ) const;
```

Retrieve rule processing priority.

##### Parameters

n/a

##### Return Value

[int](http://en.cppreference.com/w/cpp/language/types) representing rule processing priority.

##### Exceptions

n/a

#### Rule::set_priority

```C++
void set_priority( const int value );
```

Alter rule's processing priority.

##### Parameters

| name       | type                                                           | default value | direction |
|:----------:|----------------------------------------------------------------|:-------------:|:---------:|
| value      | [int](http://en.cppreference.com/w/cpp/language/types)         |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

### Service

The service is responsible for managing the publicly available RESTful resources, HTTP compliance, scheduling of the socket data and insuring incoming requests are processed in a timely fashion.

#### Methods

-	[constructor](#serviceconstructor)
-	[destructor](#servicedestructor)
-	[is_up](#serviceis_up)
-	[is_down](#serviceis_down)
-	[stop](#servicestop)
-	[start](#servicestart)
-	[restart](#servicerestart)
-	[add_rule](#serviceadd_rule)
-	[publish](#servicepublish)
-	[suppress](#servicesuppress)
-	[schedule](#serviceschedule)
-	[get_uptime](#serviceget_uptime)
-	[get_http_uri](#serviceget_http_uri)
-	[get_https_uri](#serviceget_https_uri)
-	[set_logger](#serviceset_logger)
-	[set_session_manager](#serviceset_session_manager)
-	[set_ready_handler](#serviceset_ready_handler)
-	[set_signal_handler](#serviceset_signal_handler)
-	[set_not_found_handler](#serviceset_not_found_handler)
-	[set_method_not_allowed_handler](#serviceset_method_not_allowed_handler)
-	[set_method_not_implemented_handler](#serviceset_method_not_implemented_handler)
-	[set_failed_filter_validation_handler](#serviceset_failed_filter_validation_handler)
-	[set_error_handler](#serviceset_error_handler)
-	[set_authentication_handler](#serviceset_authentication_handler)

#### Service::constructor

```C++
Resource( void );
```

Initialises a new class instance; see also [destructor](#servicedestructor).

##### Parameters

n/a

##### Return Value

n/a

##### Exceptions

n/a

#### Service::destructor

```C++
virtual ~Service( void );
```

Clean-up class instance; see also [constructor](#serviceconstructor).

##### Parameters

n/a

##### Return Value

n/a

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).

#### Service::is_up

```C++
bool is_up( void ) const;
```

Return boolean value indicating if the service is currently online and serving incoming requests.

##### Parameters

n/a

##### Return Value

Boolean true if the service is online, else false.

##### Exceptions

n/a

#### Service::is_up

```C++
bool is_down( void ) const;
```

Return boolean value indicating if the service is currently offline and serving incoming requests.

##### Parameters

n/a

##### Return Value

Boolean true if the service is offline, else false.

##### Exceptions

n/a

#### Service::stop

```C++
void stop( void ) const;
```

Shut the service down, closing open sessions and terminating threads that may be running.

##### Parameters

n/a

##### Return Value

Boolean true if the service is offline, else false.

##### Exceptions

n/a

#### Service::start

```C++
void start( const std::shared_ptr< const Settings >& settings = nullptr );
```

Start the service with the supplied settings, otherwise default values will be set.

##### Parameters

| name       | type                                                                  | default value | direction |
|:----------:|-----------------------------------------------------------------------|:-------------:|:---------:|
| settings   | [std::shared_ptr](http://en.cppreference.com/w/cpp/memory/shared_ptr) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Service::restart

```C++
void restart( const std::shared_ptr< const Settings >& settings = nullptr );
```

Restart the service with the supplied settings, otherwise default values will be set.

##### Parameters

| name       | type                                                                  | default value | direction |
|:----------:|-----------------------------------------------------------------------|:-------------:|:---------:|
| settings   | [std::shared_ptr](http://en.cppreference.com/w/cpp/memory/shared_ptr) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Service::add_rule

```C++
void add_rule( const std::shared_ptr< Rule >& rule );

void add_rule( const std::shared_ptr< Rule >& rule, const int priority );
```

Add incoming request processing rule; see also [Rule](#rule).

##### Parameters

| name       | type                                                  | default value | direction |
|:----------:|-------------------------------------------------------|:-------------:|:---------:|
| rule       | [Rule](#rule)                                         |      n/a      |   input   |
| priority   | [int](http://en.cppreference.com/w/cpp/types/integer) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Service::publish

```C++
void publish( const std::shared_ptr< const Resource >& resource );
```

Publish a RESTful resource for public consumption; see also [Resource](#resource).

##### Parameters

| name       | type                                                                  | default value | direction |
|:----------:|-----------------------------------------------------------------------|:-------------:|:---------:|
| resource   | [std::shared_ptr](http://en.cppreference.com/w/cpp/memory/shared_ptr) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Service::suppress

```C++
void suppress( const std::shared_ptr< const Resource >& resource );
```

Suppress an already published RESTful resource; see also [Resource](#resource).

##### Parameters

| name       | type                                                                  | default value | direction |
|:----------:|-----------------------------------------------------------------------|:-------------:|:---------:|
| resource   | [std::shared_ptr](http://en.cppreference.com/w/cpp/memory/shared_ptr) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Service::schedule

```C++
void schedule( const std::function< void ( void ) >& task, const std::chrono::milliseconds& interval = std::chrono::milliseconds::zero( ) );
```

Place a task on the services event loop for future processing. If an interval is supplied the task will be continual queued with the specified delay.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| task       | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |
| interval   | [std::chrono::milliseconds](http://en.cppreference.com/w/cpp/chrono/duration) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Service::get_uptime

```C++
const std::chrono::seconds get_uptime( void ) const;
```

Return the number of seconds that have passed since the service was brought online.

##### Parameters

n/a

##### Return Value

Number of seconds since calling [start](#servicestart).

##### Exceptions

n/a

#### Service::get_http_uri

```C++
const std::shared_ptr< const Uri > get_http_uri( void ) const;
```

Return a URI representing the HTTP endpoint; see also [URI](#uri).

##### Parameters

n/a

##### Return Value

URI representing HTTP endpoint.

##### Exceptions

n/a

#### Service::get_https_uri

```C++
const std::shared_ptr< const Uri > get_https_uri( void ) const;
```

Return a URI representing the HTTPS endpoint; see also [URI](#uri).

##### Parameters

n/a

##### Return Value

URI representing HTTPS endpoint.

##### Exceptions

n/a

#### Service::set_logger

```C++
void set_logger( const std::shared_ptr< Logger >& value );
```

Set the logger instance to be used; see also [Logger](#logger).

##### Parameters

| name       | type                                                                  | default value | direction |
|:----------:|-----------------------------------------------------------------------|:-------------:|:---------:|
| value      | [std::shared_ptr](http://en.cppreference.com/w/cpp/memory/shared_ptr) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Service::set_session_manager

```C++
void set_session_manager( const std::shared_ptr< SessionManager >& value );
```

Set the manager to use for the creation, loading, and purging of HTTP sessions; see also [Session Manager](#sessionmanager).

##### Parameters

| name       | type                                                                  | default value | direction |
|:----------:|-----------------------------------------------------------------------|:-------------:|:---------:|
| value      | [std::shared_ptr](http://en.cppreference.com/w/cpp/memory/shared_ptr) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Service::set_signal_handler

```C++
void set_signal_handler( const int signal, const std::function< void ( const int ) >& value );
```

Set a handler for the specified system signal number.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| signal     | [int](http://en.cppreference.com/w/cpp/types/integer)                         |      n/a      |   input   |
| value      | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Service::set_not_found_handler

```C++
void set_not_found_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value );
```

If an incoming HTTP request cannot be matched a known resource its session will be handed over to the resource not found handler.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| value      | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Service::set_method_not_allowed_handler

```C++
void set_not_found_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value );
```

If an incoming HTTP request cannot be matched a known resource method handler its session will be routed over to the method not found handler.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| value      | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Service::set_method_not_implemented_handler

```C++
void set_method_not_implemented_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value );
```

If none of the service resources have a handler for an incoming HTTP request method its session shall be routed to the method not implemented handler.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| value      | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Service::set_failed_filter_validation_handler

```C++
void set_failed_filter_validation_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value );
```

If a resource has filters applied to one or more of it's endpoints but has no specific failed filter validation handler, the global service handler will be invoked if set.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| value      | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Service::set_error_handler

```C++
void set_error_handler( const std::function< void ( const int, const std::exception&, const std::shared_ptr< Session > ) >& value );
```

If an error occurs during processing and no resource specific error handler can be obtained, the global service error handler will be invoked if set.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| value      | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Service::set_authentication_handler

```C++
void set_authentication_handler( const std::function< void ( const std::shared_ptr< Session >, const std::function< void ( const std::shared_ptr< Session > ) >& ) >& value );
```

Set a service wide authentication handler before invoking resource specific authentication handlers.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| value      | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

### Session

Represents a conversation between a client and the service. Internally this class holds the network state and exposes public functionality to interact with the service event-loop for asynchronous data acquisition and/or sleep states.

#### Methods

-	[constructor](#sessionconstructor)
-	[destructor](#sessiondestructor)
-	[has](#sessionhas)
-	[erase](#sessionerase)
-	[keys](#sessionkeys)
-	[is_open](#sessionis_open)
-	[is_closed](#sessionis_closed)
-	[close](#sessionclose)
-	[yield](#sessionyield)
-	[fetch](#sessionfetch)
-	[upgrade](#sessionupgrade)
-	[sleep_for](#sessionsleep_for)
-	[get_id](#sessionget_id)
-	[get_origin](#sessionget_origin)
-	[get_destination](#sessionget_destination)
-	[get_request](#sessionget_request)
-	[get_resource](#sessionget_resource)
-	[get_headers](#sessionget_headers)
-	[get](#sessionget)
-	[set_id](#sessionset_id)
-	[set](#sessionset)
-	[add_header](#sessionadd_header)
-	[set_header](#sessionset_header)
-	[set_headers](#sessionset_headers)

#### Session::constructor

```C++
Session( const std::string& id );
```

Initialises a new class instance; see also [destructor](#sessiondestructor).

##### Parameters

| name       | type                                                                | default value | direction |
|:----------:|---------------------------------------------------------------------|:-------------:|:---------:|
| value      | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Session::destructor

```C++
virtual ~Session( void );
```

Clean-up class instance; see also [constructor](#sessionconstructor).

##### Parameters

n/a

##### Return Value

n/a

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).

#### Session::has

```C++
bool has( const std::string& name ) const;
```

Test if a session has session-data under the supplied name.

##### Parameters

| name       | type                                                                | default value | direction |
|:----------:|---------------------------------------------------------------------|:-------------:|:---------:|
| name       | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

Boolean true if the data is available.

##### Exceptions

n/a

#### Session::erase

```C++
void erase( const std::string& name = "" );
```

If session-data is available under the supplied name it is removed. If name is empty all data is erased.

##### Parameters

| name       | type                                                                | default value | direction |
|:----------:|---------------------------------------------------------------------|:-------------:|:---------:|
| name       | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Session::keys

```C++
const std::set< std::string > keys( void ) const;
```

Return a collection of session-data keys.

##### Parameters

n/a

##### Return Value

Collection of valid session-data keys.

##### Exceptions

n/a

#### Session::is_open

```C++
bool is_open( void ) const;
```

Return the status of the underlying Session socket.

##### Parameters

n/a

##### Return Value

Boolean true if the session is active.

##### Exceptions

n/a

#### Session::is_closed

```C++
bool is_closed( void ) const;
```

Return the status of the underlying Session socket.

##### Parameters

n/a

##### Return Value

Boolean true if the session is inactive.

##### Exceptions

n/a

#### Session::close

```C++
void close( const Bytes& body );

void close( const Response& response );

void close( const std::string& body = "" );

void close( const int status, const Bytes& body );

void close( const int status, const std::string& body = "" );

void close( const int status, const std::multimap< std::string, std::string >& headers );

void close( const int status, const std::string& body, const std::multimap< std::string, std::string >& headers );

void close( const int status, const Bytes& body, const std::multimap< std::string, std::string >& headers );
```

Close an active session returning a tailored HTTP response based on the supplied parameters.

##### Parameters

| name       | type                                                                | default value | direction |
|:----------:|---------------------------------------------------------------------|:-------------:|:---------:|
| status     | [int](http://en.cppreference.com/w/cpp/types/integer)               |      n/a      |   input   |
| body       | [Bytes](#bytebytes)                                                 |      n/a      |   input   |
| body       | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |
| headers    | [std::multimap](http://en.cppreference.com/w/cpp/container/multimap)|      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Session::yield

```C++
void yield( const Bytes& data, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );

void yield( const std::string& data, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );

void yield( const Response& response, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );

void yield( const int status, const std::string& body, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );

void yield( const int status, const Bytes& body = { }, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );

void yield( const int status, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );

void yield( const int status, const Bytes& body, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );

void yield( const int status, const std::string& body, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );
```

Return a tailored HTTP response based on the supplied parameters without closing the underlying socket connection; On completion invoke the callback.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| status     | [int](http://en.cppreference.com/w/cpp/types/integer)                         |      n/a      |   input   |
| body       | [Bytes](#bytebytes)                                                           |      n/a      |   input   |
| body       | [std::string](http://en.cppreference.com/w/cpp/string/basic_string)           |      n/a      |   input   |
| headers    | [std::multimap](http://en.cppreference.com/w/cpp/container/multimap)          |      n/a      |   input   |
| callback   | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Session::fetch

```C++
void fetch( const std::size_t length, const std::function< void ( const std::shared_ptr< Session >, const Bytes& ) >& callback );
            
void fetch( const std::string& delimiter, const std::function< void ( const std::shared_ptr< Session >, const Bytes& ) >& callback );
```

1) Fetch length bytes from the underlying socket connection.

2) Fetch bytes from the underlying socket connection until encountering the delimiter.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| length     | [std::size_t](http://en.cppreference.com/w/cpp/types/size_t)                  |      n/a      |   input   |
| delimiter  | [std::string](http://en.cppreference.com/w/cpp/string/basic_string)           |      n/a      |   input   |
| callback   | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Session::upgrade

```C++
void upgrade( const int status, const std::function< void ( const std::shared_ptr< WebSocket > ) >& callback );

void upgrade( const int status, const Bytes& body, const std::function< void ( const std::shared_ptr< WebSocket > ) >& callback );

void upgrade( const int status, const std::string& body, const std::function< void ( const std::shared_ptr< WebSocket > ) >& callback );

void upgrade( const int status, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< WebSocket > ) >& callback );

void upgrade( const int status, const Bytes& body, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< WebSocket > ) >& callback );

void upgrade( const int status, const std::string& body, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< WebSocket > ) >& callback );
```

Return a tailored HTTP response based on the supplied parameters and upgrade to the WebSocket protocol; On completion invoke the callback.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| status     | [int](http://en.cppreference.com/w/cpp/types/integer)                         |      n/a      |   input   |
| body       | [Bytes](#bytebytes)                                                           |      n/a      |   input   |
| body       | [std::string](http://en.cppreference.com/w/cpp/string/basic_string)           |      n/a      |   input   |
| headers    | [std::multimap](http://en.cppreference.com/w/cpp/container/multimap)          |      n/a      |   input   |
| callback   | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Session::sleep_for

```C++
void sleep_for( const std::chrono::milliseconds& delay, const std::function< void ( const std::shared_ptr< Session > ) >& callback );
```

Place a task on the [Service](#service) event loop to be run in delay milliseconds.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| delay      | [std::chrono::milliseconds](http://en.cppreference.com/w/cpp/chrono/duration) |      n/a      |   input   |
| callback   | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Session::get_id

```C++
const std::string& get_id( void ) const;
```

Return a string uniquely identifying this session instance.

##### Parameters

n/a

##### Return Value

[std::string](http://en.cppreference.com/w/cpp/utility/functional/function) representing a unique session identifier.

##### Exceptions

n/a

#### Session::get_origin

```C++
const std::string get_origin( void ) const;
```

Return a string representing an Internet Protocol address and port number identifying the source of the current HTTP request.

##### Parameters

n/a

##### Return Value

[std::string](http://en.cppreference.com/w/cpp/utility/functional/function) representing the source network endpoint.
##### Exceptions

n/a

#### Session::get_destination

```C++
const std::string get_destination( void ) const;
```

Return a string representing an Internet Protocol address and port number identifying the original destination of the current HTTP request.

##### Parameters

n/a

##### Return Value

[std::string](http://en.cppreference.com/w/cpp/utility/functional/function) representing a destination network endpoint.

##### Exceptions

n/a

#### Session::get_request

```C++
const std::shared_ptr< const Request > get_request(  void ) const;
```

Return the currently active HTTP request.

##### Parameters

n/a

##### Return Value

[std::shared_ptr](http://en.cppreference.com/w/cpp/memory/shared_ptr) representing a HTTP request.

##### Exceptions

n/a

#### Session::get_resource

```C++
const std::shared_ptr< const Resource > get_resource( void ) const;
```

Return the currently active RESTful resource.

##### Parameters

n/a

##### Return Value

[std::shared_ptr](http://en.cppreference.com/w/cpp/memory/shared_ptr) representing a HTTP request.

##### Exceptions

n/a

#### Session::get_headers

```C++
const std::multimap< std::string, std::string >& get_headers( void ) const;
```

Return the default session header that must be present on each HTTP response.

##### Parameters

n/a

##### Return Value

[std::multimap](http://en.cppreference.com/w/cpp/container/multimap) representing a collection of HTTP headers.

##### Exceptions

n/a

#### Session::get

```C++
const ContextValue& get( const std::string& name ) const;

const ContextValue& get( const std::string& name, const ContextValue& default_value ) const;
```

Return the session data identified by name.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| name       | [std::string](http://en.cppreference.com/w/cpp/string/basic_string)           |      n/a      |   input   |
| value      | [std::any](http://en.cppreference.com/w/cpp/utility/any)                      |      n/a      |   input   |

##### Return Value

[std::any](http://en.cppreference.com/w/cpp/utility/any) session data item.

##### Exceptions

n/a

#### Session::set_id

```C++
void set_id( const std::string& value );
```

Set a unique session identifier.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| value      | [std::string](http://en.cppreference.com/w/cpp/string/basic_string)           |      n/a      |   input   |

##### Return Value

[std::any](http://en.cppreference.com/w/cpp/utility/any) session data item.

##### Exceptions

n/a

#### Session::set

```C++
void set( const std::string& name, const ContextValue& value );
```

Set a unique session identifier.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| name       | [std::string](http://en.cppreference.com/w/cpp/string/basic_string)           |      n/a      |   input   |
| value      | [std::any](http://en.cppreference.com/w/cpp/utility/any)                      |      n/a      |   input   |

##### Return Value

[std::any](http://en.cppreference.com/w/cpp/utility/any) session data item.

##### Exceptions

n/a

#### Session::add_header

```C++
void add_header( const std::string& name, const std::string& value );
```

Add a default HTTP header to the session, existing headers that share the same name will not be altered.

##### Parameters

| name  | type                                                                | default value | direction |
|:-----:|---------------------------------------------------------------------|:-------------:|:---------:|
| name  | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |
| value | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Session::set_header

```C++
void set_header( const std::string& name, const std::string& value );
```

Set a default HTTP header for the session, existing headers that share the same name will be erased.

##### Parameters

| name  | type                                                                | default value | direction |
|:-----:|---------------------------------------------------------------------|:-------------:|:---------:|
| name  | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |
| value | [std::string](http://en.cppreference.com/w/cpp/string/basic_string) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### Session::set_headers

```C++
void set_headers( const std::multimap< std::string, std::string >& values );
```

Set default HTTP headers for the session, existing headers will be erased; see also [get_headers](#sessionget_headers).

##### Parameters

| name   | type                                                                 | default value | direction |
|:------:|----------------------------------------------------------------------|:-------------:|:---------:|
| values | [std::multimap](http://en.cppreference.com/w/cpp/container/multimap) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

### SessionManager

Abstract Class detailing the required contract for SessionManager extensions. No default implementation is supplied with the codebase and it is the responsibility of third-party developers to implement desired characteristics.

#### Methods

-	[constructor](#sessionmanagerconstructor)
-	[destructor](#sessionmanagerdestructor)
-	[stop](#sessionmanagerstop)
-	[start](#sessionmanagerstart)
-	[create](#sessionmanagercreate)
-	[load](#sessionmanagerload)
-	[save](#sessionmanagersave)

#### SessionManager::constructor

```C++
SessionManager( void );
```

Initialises a new class instance; see also [destructor](#sessionmanagerdestructor).

##### Parameters

n/a

##### Return Value

n/a

##### Exceptions

n/a

#### SessionManager::destructor

```C++
virtual ~SessionManager( void );
```

Clean-up class instance; see also [constructor](#sessionconstructor).

##### Parameters

n/a

##### Return Value

n/a

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).

#### SessionManager::stop

```C++
virtual void stop( void );
```

Shutdown an active SessionManager.

##### Parameters

n/a

##### Return Value

n/a

##### Exceptions

n/a

#### SessionManager::start

```C++
virtual void start( const std::shared_ptr< const Settings >& settings );
```

Start the Session Manager, the settings supplied are identical to those given to [Service::start](servicestart).

##### Parameters

| name   | type                                                                    | default value | direction |
|:------:|-------------------------------------------------------------------------|:-------------:|:---------:|
| settings | [std::shared_ptr](http://en.cppreference.com/w/cpp/memory/shared_ptr) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a


#### SessionManager::create

```C++
virtual void create( const std::function< void ( const std::shared_ptr< Session > ) >& callback );
```

Create a new [Session](#session) instance passing it into callback.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| callback   | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### SessionManager::load

```C++
virtual void load( const std::shared_ptr< Session > session, const std::function< void ( const std::shared_ptr< Session > ) >& callback );
```

Load previous session data into the supplied session before passing it to callback.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| session    | [std::shared_ptr](http://en.cppreference.com/w/cpp/memory/shared_ptr)         |      n/a      |   input   |
| callback   | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

#### SessionManager::save

```C++
virtual void save( const std::shared_ptr< Session > session, const std::function< void ( const std::shared_ptr< Session > ) >& callback );
```

Save session for later retrieval.

##### Parameters

| name       | type                                                                          | default value | direction |
|:----------:|-------------------------------------------------------------------------------|:-------------:|:---------:|
| session    | [std::shared_ptr](http://en.cppreference.com/w/cpp/memory/shared_ptr)         |      n/a      |   input   |
| callback   | [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) |      n/a      |   input   |

##### Return Value

n/a

##### Exceptions

n/a

### Further Reading

[C++ Standard](https://isocpp.org/std/the-standard) - The current ISO C++ standard is officially known as ISO International Standard ISO/IEC 14882:2014(E) – Programming Language C++. Want to read the ISO C++ standard, or working drafts of the standard? You have several options, most of them free.

[C++ Reference](http://en.cppreference.com/) - Comprehensive C++ and Standard Template Library (STL) reference.

[Effective STL](https://www.amazon.com/Effective-STL-Specific-Standard-Template/dp/0201749629) - Written for the intermediate or advanced C++ programmer, renowned C++ expert Scott Meyers provides essential techniques for getting more out of the Standard Template Library in Effective STL, a tutorial for doing more with this powerful library.

[Effective C++](https://www.amazon.com/Effective-Specific-Improve-Programs-Designs/dp/0321334876) - “Every C++ professional needs a copy of Effective C++. It is an absolute must-read for anyone thinking of doing serious C++ development. If you’ve never read Effective C++ and you think you know everything about C++, think again.” — Steve Schirripa, Software Engineer, Google
