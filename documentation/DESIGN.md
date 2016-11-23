Overview
--------

This document is intended to communicate core architectural decisions within the system. For this reason alone accuracy has suffered. It does not concern itself with interface specifics and primarily focuses on architectural decisions made during the design and development phase, see [API](API.md) for contract details.

All class definitions within the system strictly adhere to the [Opaque Pointer](https://en.wikipedia.org/wiki/Opaque_pointer) idiom. However, this level of detail in the following suite of class diagrams is omitted for clarity; along with pointers, references and other background noise.

Unless otherwise specified all primary data-types originate within the Standard Template Library (STL).

Interpretation
--------------

The key words “MUST”, “MUST NOT”, “REQUIRED”, “SHALL”, “SHALL NOT”, “SHOULD”, “SHOULD NOT”, “RECOMMENDED”, “MAY”, and “OPTIONAL” in this document are to be interpreted as described in [RFC 2119](http://tools.ietf.org/pdf/rfc2119.pdf).

Table of Contents
-----------------

1.	[Overview](#overview)
2.	[Interpretation](#interpretation)
3.	[Terminology](#terminology)
4.	[System Entities](#system-entities)
5.	[Entity Interactions](#entity-interactions)
6.	[Dependency Tree](#dependency-tree)
7.	[Event Loop](#event-loop)
8.	[Thread Allocation](#thread-allocation)
9.	[Future Direction](#future-direction)
10.	[Further Reading](#further-reading)

Terminology
-----------

| Term         | Definition                                                                                                                  |
|--------------|-----------------------------------------------------------------------------------------------------------------------------|
| Resource     | A network addressable entity i.e Queue.                                                                                     |
| Service      | A server responsible for request routing and processing.                                                                    |
| Client       | A remote endpoint responsible for generating requests.                                                                      |
| Logger       | A component making a systematic recording of events, observations, or measurements.                                         |
| Charset      | A CHARacter SET is used to represent a repertoire of symbols i.e UTF-8.                                                     |
| URI          | Uniform Resource Identifier.                                                                                                |
| UUID         | Universally Unique IDentifier.                                                                                              |
| Path         | String identifier uniquely addressing a resource.                                                                           |

System Entities
---------------

-	[Byte/Bytes](#bytebytes)
-	[Resource](#resource)
-	[Callback](#callback)
-	[StatusCode](#statuscode)
-	[String::Option](#stringoption)
-	[String](#string)
-	[URI](#uri)
-	[Request](#request)
-	[Response](#response)
-	[Session](#session)
-	[SessionManager](#sessionmanager)
-	[Rule](#rule)
-	[SSLSettings](#sslsettings)
-	[Settings](#settings)
-	[WebSocket](#websocket)
-	[WebSocketMessage](#websocketmessage)
-	[WebSocketMessage::OpCode](#websocketmessageopcode)
-	[Logger](#logger)
-	[Logger::Level](#loggerlevel)
-	[Service](#service)

### Byte/Bytes

Byte represents an unsigned 8-bit wide data-type, Bytes provides container functionality with STL [vector](http://en.cppreference.com/w/cpp/container/vector) collection semantics.

```
+----------------+
|   <<typedef>>  |
|      Bytes     |
+----------------+
| vector< Byte > |
+--------@-------+
         |
         |
         |
+--------+-------+
|   <<typedef>>  |
|      Byte      |
+----------------+
|     uint8_t    |
+----------------+
```

### Resource

Resource represents an network communication endpoint. This is the primary data-structure used throughout to represent RESTful resources. All resource specific filteration, request processing rules, and authentication must be placed on this entity.

```
+------------------------------------------------------------------------+
|                                <<class>>                               |
|                                Resources                               |
+------------------------------------------------------------------------+
| + add_rule(Rule)                                                 void  |
| + add_rule(Rule, integer)                                        void  |
| + set_path(string)                                               void  |
| + set_paths(set<string>)                                         void  |
| + set_default_header(string,string)                              void  |
| + set_default_headers(multimap<string,string>)                   void  |
| + set_failed_filter_validation_handler(Callback)                 void  |
| + set_error_handler(Callback)                                    void  |
| + set_authentication_handler(void)                               void  |
| + set_method_handler(string,Callback)                            void  |
| + set_method_handler(string,multimap<string,string>,Callback)    void  |
+------------------------------------------------------------------------+
```

### Callback

Represents a functor with variable parameters and return; this is used to help illustrate the design without introducing unnecessary complexity.

```
+-----------------+
|   <<typedef>>   |
|    Callback     |
+-----------------+
|  std::function  |
+-----------------+
```

### StatusCode

[Enumeration](http://en.cppreference.com/w/cpp/language/enum) of HTTP response status codes as outlined in [RFC 7231 sub-section 6.1](https://tools.ietf.org/html/rfc7231#section-6.1).

```
 +---------------------------+
 |         <<enum>>          |
 |        StatusCode         |
 +---------------------------+
 | See RFC 7231 for details. |
 +---------------------------+
```

### String::Option

[Enumeration](http://en.cppreference.com/w/cpp/language/enum) of possible string case sensitivity options.

```
 +--------------------+
 |      <<enum>>      |
 |   String::Option   |
 +--------------------+
 | + CASE_SENSITIVE   |
 | + CASE_INSENSITIVE |
 +------------------ -+
```

### String

Utility class with static scope offering a common suite of string manipulation routines.

```
 +---------------------------------------------------------------+
 |                           <<static>>                          |
 |                             String                            |
 +---------------------------------------------------------------+
 | + to_bytes(string)                             Bytes          |
 | + to_string(Bytes)                             string         |
 | + lowercase(string)                            string         |
 | + uppercase(string,string)                     string         |
 | + format(char*,...)                            string         |
 | + join(multimap<string,string>,string,string)  string         |
 | + remove(string,string,Option)                 string         |
 | + replace(string,string,string,Option)         string         |
 | + split(string,string)                         vector<string> |
 +--------------------------------^------------------------------+
                                  |
                                  |
                                  |
                 +----------------v----------------+
                 |             <<enum>>            |
                 |          String::Option         |
                 +---------------------------------+
                 | See String::Option for details. |
                 +---------------------------------+
```

### URI

Represents a Uniform Resource Identifier as specified in [RFC 3986](https://www.ietf.org/rfc/rfc3986.txt).

> A generic URI is of the form:
>
> scheme:[//[user:password@]host\[:port]][/]path[?query][#fragment]

```
 +-------------------------------------------------------+
 |                        <<class>>                      |
 |                           Uri                         |
 +-------------------------------------------------------+
 | + is_relative(void)           boolean                 |
 | + is_absolute(void)           boolean                 |
 | + is_valid(string)            boolean                 |
 | + parse(string)               Uri                     |
 | + to_string(void)             string                  |
 | + decode(Bytes)               string                  |
 | + decode(string)              string                  |
 | + decode_parameter(string)    string                  |
 | + encode(Bytes)               string                  |
 | + encode(string)              string                  |
 | + encode_parameter(string)    string                  |
 | + get_port(void)              unsigned 16-bit integer |
 | + get_path(void)              string                  |
 | + get_query(void)             string                  |
 | + get_scheme(void)            string                  |
 | + get_fragment(void)          string                  |
 | + get_username(void)          string                  |
 | + get_password(void)          string                  |
 | + get_authority(void)         string                  |
 | + get_query_parameters(void)  multimap<string,string> |
 +-------------------------------------------------------+
```

### Request

Represents a HTTP request with additional helper methods for manipulating data, and code readability.

```
 +--------------------------------------------------------------------------------+
 |                                   <<class>>                                    |
 |                                    Request                                     |
 +--------------------------------------------------------------------------------+
 | + has_header(string)                                   boolean                 |
 | + has_path_parameter(string)                           boolean                 |
 | + has_query_parameter(string)                          boolean                 |
 | + get_port(void)                                       unsigned 16-bit integer |
 | + get_version(void)                                    double                  |
 | + get_body(void)                                       Bytes                   |
 | + get_body(Callback)                                   Bytes                   |
 | + get_response(void)                                   Response                |
 | + get_host(Callback)                                   string                  |
 | + get_path(Callback)                                   string                  |
 | + get_method(Callback)                                 string                  |
 | + get_protocol(Callback)                               string                  |
 | + get_header(string,template<Type>)                    template<Type>          |
 | + get_header(string,string)                            string                  |
 | + get_header(string,Callback)                          string                  |
 | + get_headers(string)                                  multimap<string,string> |
 | + get_query_parameter(string,template<Type>)           template<Type>          |
 | + get_query_parameter(string,string)                   string                  |
 | + get_query_parameter(string,Callback)                 string                  |
 | + get_query_parameters(string)                         multimap<string,string> |
 | + get_path_parameter(string,template<Type>)            template<Type>          |
 | + get_path_parameter(string,string)                    string                  |
 | + get_path_parameter(string,Callback)                  string                  |
 | + get_path_parameters(string)                          map<string,string>      |
 | + set_body(Bytes)                                      void                    |
 | + set_body(string)                                     void                    |
 | + set_port(unsigned 16-bit integer)                    void                    |
 | + set_version(double)                                  void                    |
 | + set_path(string)                                     void                    |
 | + set_host(string)                                     void                    |
 | + set_method(string)                                   void                    |
 | + set_protocol(string)                                 void                    |
 | + add_header(string,string)                            void                    |
 | + set_header(string,string)                            void                    |
 | + set_headers(multimap<string,string>)                 void                    |
 | + set_query_parameter(string,string)                   void                    |
 | + set_query_parameters(multimap<string,string>)        void                    |
 +------------------------------------------@-------------------------------------+
                                            | 1
                                            |
                                            |
                                            | 1
                         +------------------+-----------------+
                         |             <<class>>              |
                         |              Response              |
                         +------------------------------------+
                         |      See Response for details.     |
                         +------------------------------------+
```

### Response

Represents a HTTP response with additional helper methods for manipulating data, and improving code readability.

```
 +-----------------------------------------------------------------+
 |                              <<class>>                          |
 |                               Response                          |
 +-----------------------------------------------------------------+
 | + has_header(string)                    boolean                 |
 | + get_body(void)                        Bytes                   |
 | + get_body(Callback)                    Bytes                   |
 | + get_version(void)                     double                  |
 | + get_status_code(void)                 integer                 |
 | + get_header(string,template<Type>)     template<Type>          |
 | + get_header(string,string)             string                  |
 | + get_header(string,Callback)           string                  |
 | + get_headers(string)                   multimap<string,string> |
 | + set_body(Bytes)                       void                    |
 | + set_body(string)                      void                    |
 | + set_version(double)                   void                    |
 | + set_status_code(integer)              void                    |
 | + set_protocol(string)                  void                    |
 | + set_status_message(string)            void                    |
 | + add_header(string,string)             void                    |
 | + set_header(string,string)             void                    |
 | + set_headers(multimap<string,string>)  void                    |
 +-----------------------------------------------------------------+
```

### Session

Represents a conversation between a client and the service. Internally this class holds the network state and exposes public functionality to interact with the service event-loop for asynchronous data acquisition and/or sleep states.

```
 +-------------------------------------------------------------------------------------+
 |                                      <<class>>                                      |
 |                                       Session                                       |
 +-------------------------------------------------------------------------------------+
 | + has(string)                                               boolean                 |
 | + erase(string)                                             void                    |
 | + keys(void)                                                set<string>             |
 | + is_open(void)                                             boolean                 |
 | + is_closed(void)                                           boolean                 |
 | + close(Bytes)                                              void                    |
 | + close(Response)                                           void                    |
 | + close(string)                                             void                    |
 | + close(integer,Bytes)                                      void                    |
 | + close(integer,string)                                     void                    |
 | + close(integer,multimap<string,string>)                    void                    |
 | + close(integer,string,multimap<string,string>)             void                    |
 | + close(integer,Bytes,multimap<string,string>)              void                    |
 | + yield(Bytes,Callback)                                     void                    |
 | + yield(string,Callback)                                    void                    |
 | + yield(Response,Callback)                                  void                    |
 | + yield(integer,string,Callback)                            void                    |
 | + yield(integer,Bytes,Callback)                             void                    |
 | + yield(integer,multimap<string,string>,Callback)           void                    |
 | + yield(integer,Bytes,multimap<string,string>,Callback)     void                    |
 | + yield(integer,string,multimap<string,string>,Callback)    void                    |
 | + fetch(size_t,Callback)                                    void                    |
 | + fetch(string,Callback)                                    void                    |
 | + upgrade(integer,Callback)                                 void                    |
 | + upgrade(integer,Bytes,Callback)                           void                    |
 | + upgrade(integer,string,Callback)                          void                    |
 | + upgrade(integer,multimap<string,string>,Callback)         void                    |
 | + upgrade(integer,Bytes,multimap<string,string>,Callback)   void                    |
 | + upgrade(integer,string,multimap<string,string>,Callback)  void                    |
 | + sleep_for(milliseconds,Callback)                          void                    |
 | + get_id(void)                                              string                  |
 | + get_origin(void)                                          string                  |
 | + get_destination(void)                                     string                  |
 | + get_request(void)                                         Request                 |
 | + get_resource(void)                                        Resource                |
 | + get_headers(void)                                         multimap<string,string> |
 | + get(string)                                               ContextValue            |
 | + get(string,ContextValue)                                  ContextValue            |
 | + set_id(string)                                            void                    |
 | + set(string,ContextValue)                                  void                    |
 | + add_headerstring,string)                                  void                    |
 | + set_header(string,string)                                 void                    |
 | + set_headers(multimap<string,string>)                      void                    |
 +----------------------------------------@--------------------------------------------+
                                        1 | 1
                                          |
                       +------------------+-------------------+
                       |                                      |
                       |                                      |
                     1 |                                      | 1
    +------------------+----------------+  +------------------+-----------------+
    |             <<class>>             |  |             <<class>>              |
    |              Request              |  |              Resource              |
    +-----------------------------------+  +------------------------------------+
    |      See Request for details.     |  |       See Resource for details.    |
    +-----------------------------------+  +------------------------------------+
```

### SessionManager

Abstract Class detailing the required contract for SessionManager extensions. No default implementation is supplied with the codebase and it is the responsibility of third-party developers to implement desired characteristics.

```
  +---------------------------------+
  |         <<abstract>>            |
  |        SessionManager           |
  +---------------------------------+         +---------------------------+
  | + stop(void)               void |         |         <<class>>         |
  | + start(Settings)          void | 1     1 |          Settings         |
  | + create(Callback)         void @---------+---------------------------+
  | + load(Session,Callback)   void |         | See Settings for details. |
  | + save(Session,Callback)   void |         +---------------------------+
  +----------------^----------------+
                   |
                   |
     +-------------v------------+
     |         <<class>>        |
     |          Session         |
     +--------------------------+
     | See Session for details. |
     +--------------------------+
```

### Rule

Represents a reusable source of request validation and processing; see [Rules Engine](https://github.com/Corvusoft/restbed/tree/master/example/rules_engine/source) example for details.

```
 +-------------------------------------+
 |             <<interface>>           |
 |                 Rule                |
 +-------------------------------------+
 | + condition(Session)        boolean |
 | + action(Session,Callback)  void    |
 | + get_priority(void)        integer |
 | + set_priority(integer)     void    |
 +-----------------^-------------------+
                   |
                   |
     +-------------v------------+
     |         <<class>>        |
     |          Session         |
     +--------------------------+
     | See Session for details. |
     +--------------------------+
```

### SSLSettings

Represents Secure Socket Layer service configuration.

```
 +---------------------------------------------------------------------------+
 |                                 <<class>>                                 |
 |                                SSLSettings                                |
 +---------------------------------------------------------------------------+
 |                    See restbed::SSLSettings for details.                  |
 +---------------------------------------------------------------------------+
 | + has_disabled_http(void)                         boolean                 |
 | + has_enabled_sslv2(void)                         boolean                 |
 | + has_enabled_sslv3(void)                         boolean                 |
 | + has_enabled_tlsv1(void)                         boolean                 |
 | + has_enabled_tlsv11(void)                        boolean                 |
 | + has_enabled_tlsv12(void)                        boolean                 |
 | + has_enabled_compression(void)                   boolean                 |
 | + has_enabled_default_workarounds(void)           boolean                 |
 | + has_enabled_single_diffie_hellman_use(void)     boolean                 |
 | + get_port(void)                                  unsigned 16-bit integer |
 | + get_bind_address(void)                          string                  |
 | + get_certificate(void)                           string                  |
 | + get_passphrase(void)                            string                  |
 | + get_private_key(void)                           string                  |
 | + get_private_rsa_key(void)                       string                  |
 | + get_certificate_chain(void)                     string                  |
 | + get_temporary_diffie_hellman(void)              string                  |
 | + get_certificate_authority_pool(void)            string                  |
 | + set_port(unsigned 16-bit integer)               void                    |
 | + set_bind_address(string)                        void                    |
 | + set_http_disabled(boolean)                      void                    |
 | + set_sslv2_enabled(boolean)                      void                    |
 | + set_sslv3_enabled(boolean)                      void                    |
 | + set_tlsv1_enabled(boolean)                      void                    |
 | + set_tlsv11_enabled(boolean)                     void                    |
 | + set_tlsv12_enabled(boolean)                     void                    |
 | + set_compression_enabled(boolean)                void                    |
 | + set_default_workarounds_enabled(boolean)        void                    |
 | + set_single_diffie_hellman_use_enabled(boolean)  void                    |
 | + set_certificate(Uri)                            void                    |
 | + set_certificate_chain(Uri)                      void                    |
 | + set_certificate_authority_pool(Uri)             void                    |
 | + set_passphrase(string)                          void                    |
 | + set_private_key(Uri)                            void                    |
 | + set_private_rsa_key(Uri)                        void                    |
 | + set_temporary_diffie_hellman(Uri)               void                    |
 +--------------------------------------^------------------------------------+
                                        |
                                        |
                             +----------v-----------+
                             |      <<class>>       |
                             |         Uri          |
                             +----------------------+
                             | See Uri for details. |
                             +----------------------+
```

### Settings

Represents the primary point of Service, SessionManager, and Logger configuration.

```
 +-------------------------------------------------------------------------+
 |                                 <<class>>                               |
 |                                 Settings                                |
 +-------------------------------------------------------------------------+
 | + get_port(void)                                unsigned 16-bit integer |
 | + get_root(void)                                string                  |
 | + get_worker_limit(void)                        unsigned integer        |
 | + get_connection_limit(void)                    unsigned integer        |
 | + get_bind_address(void)                        string                  |
 | + get_case_insensitive_uris(void)               boolean                 |
 | + get_connection_timeout(void)                  milliseconds            |
 | + get_status_message(integer)                   string                  |
 | + get_status_messages(void)                     map<integer,string>     |
 | + get_property(string)                          string                  |
 | + get_properties(void)                          map<string,string>      |
 | + get_ssl_settings(void)                        SSLSettings             |
 | + get_default_headers(void)                     multimap<string,string> |
 | + set_port(unsigned 16-bit integer)             void                    |
 | + set_root(string)                              void                    |
 | + set_worker_limit(unsigned integer)            void                    |
 | + set_connection_limit(unsigned integer)        void                    |
 | + set_bind_address(string)                      void                    |
 | + set_case_insensitive_uris(boolean)            void                    |
 | + set_connection_timeout(seconds)               void                    |
 | + set_connection_timeout(milliseconds)          void                    |
 | + set_status_message(integer,string)            void                    |
 | + set_status_messages(map<integer,string>)      void                    |
 | + set_property(string,string)                   void                    |
 | + set_properties(map<string,string>)            void                    |
 | + set_ssl_settings(SSLSettings)                 void                    |
 | + set_default_header(string,string)             void                    |
 | + set_default_headers(multimap<string,string>)  void                    |
 +------------------------------------@------------------------------------+
                                      |
                                      |
                                      |
                       +--------------+---------------+
                       |          <<class>>           |
                       |         SSLSettings          |
                       +------------------------------+
                       | See SSLSettings for details. |
                       +------------------------------+                        
```

### WebSocket

Represents a WebSocket connection. Internally this class holds the network state and exposes public functionality for full-duplex client interaction.

```
                 +-----------------------------------------------------+  
                 |                       <<class>>                     |
                 |                       WebSocket                     |
                 +-----------------------------------------------------+
                 | + is_open(void)                            boolean  |
                 | + is_closed(void)                          boolean  |
                 | + close(void)                              void     |
                 | + send(Bytes,Callback)                     void     |
                 | + send(string,Callback)                    void     |
                 | + send(WebSocketMessage::OpCode,Callback)  void     |
                 | + send(WebSocketMessage,Callback)          void     |
                 | + get_key(void)                            string   |
                 | + get_logger(void)                         Logger   |
                 | + get_open_handler(void)                   Callback |
                 | + get_close_handler(void)                  Callback |
                 | + get_error_handler(void)                  Callback |
                 | + get_message_handler(void)                Callback |
                 | + set_key(string)                          void     |
                 | + set_logger(Logger)                       void     |
                 | + set_open_handler(Callback)               void     |
                 | + set_close_handler(Callback)              void     |
                 | + set_error_handler(Callback)              void     | 
                 | + set_message_handler(Callback)            void     |
                 +------------------------^----------------------------+
                                          |
                                          |
                       +------------------+---------------------+
                       |                                        |
                       |                                        |
                       |                                        |
    +------------------v----------------+  +--------------------v----------------------+
    |             <<class>>             |  |                 <<enum>>                  |
    |         WebSocketMessage          |  |          WebSocketMessage::OpCode         |
    +-----------------------------------+  +-------------------------------------------+
    | See WebSocketMessage for details. |  | See WebSocketMessage::OpCode for details. |
    +-----------------------------------+  +-------------------------------------------+
```
### WebSocketMessage

Class representing a single WebSocket data message.

```
 +--------------------------------------------------------------------------------+
 |                                     <<class>>                                  |
 |                                  WebSocketMessage                              |
 +--------------------------------------------------------------------------------+
 | + to_bytes(void)                                Bytes                          |
 | + get_data(void)                                Bytes                          |
 | + get_opcode(void)                              WebSocketMessage::OpCode       |
 | + get_mask(void)                                unsigned 32-bit integer        |
 | + get_length(void)                              unsigned  8-bit integer        |
 | + get_extended_length(void)                     unsigned 64-bit integer        |
 | + get_mask_flag(void)                           boolean                        |
 | + get_final_frame_flag(void)                    boolean                        |
 | + get_reserved_flags(void)                      tuple<boolean,boolean,boolean> |
 | + set_data(Bytes)                               void                           |
 | + set_data(string)                              void                           |
 | + set_opcode(WebSocketMessage::OpCode)          void                           |
 | + set_mask(unsigned 32-bit integer)             void                           |
 | + set_length(unsigned 8-bit integer)            void                           |
 | + set_extended_length(unsigned 64-bit integer)  void                           |
 | + set_mask_flag(boolean)                        void                           |
 | + set_final_frame_flag(boolean)                 void                           |
 | + set_reserved_flags(boolean,boolean,boolean)   void                           |
 +--------------------------------------------------------------------------------+
                                          |
                                          |
                                          |
                     +--------------------v----------------------+
                     |                 <<enum>>                  |
                     |          WebSocketMessage::OpCode         |
                     +-------------------------------------------+
                     | See WebSocketMessage::OpCode for details. |
                     +-------------------------------------------+
```

### WebSocketMessage::OpCode

[Enumeration](http://en.cppreference.com/w/cpp/language/enum) used in conjunction with the [WebSocket](#websocket) and [WebSocketMessage](#websocketmessage) to detail the message category.

```
 +--------------------------+
 |          <<enum>>        |
 | WebSocketMessage::OpCode |
 +--------------------------+
 | CONTINUATION_FRAME       |
 | TEXT_FRAME               |
 | BINARY_FRAME             |
 | CONNECTION_CLOSE_FRAME   |
 | PING_FRAME               |
 | PONG_FRAME               |
 +--------------------------+
```

### Logger

Interface detailing the required contract for logger extensions. No default logger is supplied with the codebase and it is the responsibility of third-party developers to implement the desired characteristics.

```
 +-----------------------------------------------+
 |                 <<interface>>                 |
 |                    Logger                     |
 +-----------------------------------------------+
 | + stop(void)                             void |
 | + start(Settings)                        void |
 | + log(Logger::Level,string)              void |
 | + log_if(condition,Logger::Level,string) void |
 +----------------------^------------------------+
                        |
                        |
                        |
        +---------------v----------------+
        |            <<enum>>            |
        |         Logger::Level          |
        +--------------------------------+
        | See Logger::Level for details. |
        +--------------------------------+
```

### Logger::Level

[Enumeration](http://en.cppreference.com/w/cpp/language/enum) used in conjunction with the [Logger interface](#logger) to detail the level of severity towards a particular log entry.

```
 +---------------+
 |   <<enum>>    |
 | Logger::Level |
 +---------------+
 | INFO          |
 | DEBUG         |
 | FATAL         |
 | ERROR         |
 | WARNING       |
 | SECURITY      |
 +---------------+
```

### Service

The service is responsible for managing the publicly available RESTful resources, HTTP compliance, scheduling of the socket data and insuring incoming requests are processed in a timely fashion.

```
                                           +-----------------------------------------------------------+
                                           |                          <<class>>                        |
                                           |                           Service                         |
                                           +-----------------------------------------------------------+
                                           | + is_up(void)                                     boolean |
                                           | + is_down(void)                                   boolean |
                                           | + stop(void)                                      void    |
                                           | + start(Settings)                                 void    |
                                           | + restart(Settings)                               void    |
                                           | + add_rule(Rule)                                  void    |
                                           | + add_rule(Rule,integer)                          void    |
                                           | + publish(Resource)                               void    |
                                           | + suppress(Resource)                              void    |
                                           | + schedule(Callback,milliseconds)                 void    |
                                           | + get_uptime( void )                              seconds |
                                           | + get_http_uri( void )                            Uri     |
                                           | + get_https_uri( void )                           Uri     |
                                           | + set_logger(Logger)                              void    |
                                           | + set_session_manager(SessionManager)             void    |
                                           | + set_ready_handler(Callback)                     void    |
                                           | + set_signal_handler(integer,Callback)            void    |
                                           | + set_not_found_handler(Callback)                 void    |
                                           | + set_method_not_allowed_handler(Callback)        void    |
                                           | + set_method_not_implemented_handler(Callback)    void    |
                                           | + set_failed_filter_validation_handler(Callback)  void    |
                                           | + set_error_handler(Callback)                     void    |
                                           | + set_authentication_handler(Callback)            void    |
                                           +-----------------------------O-----------------------------+
                                                                         |
                                                                         |
                          +-------------------------------+--------------+------------------+--------------------------+
                          |                               |                                 |                          |
                          |                               |                                 |                          |
                          |                               |                                 |                          |
           +--------------+------------+  +---------------+-----------------+  +------------+------------+  +----------+------------+
           |          <<class>>        |  |         <<interface>>           |  |      <<interface>>      |  |    <<interface>>      |
           |          Settings         |  |         SessionManager          |  |         Logger          |  |         Rule          |
           +---------------------------+  +---------------------------------+  +-------------------------+  +-----------------------+
           | See Settings for details. |  | See SessionManager for details. |  | See Logger for details. |  | See Rule for details. |
           +---------------------------+  +---------------------------------+  +-------------------------+  +-----------------------+
```

Entity Interactions
-------------------

### Request Processing

```
[client]                              [service]                         [session manager]                        [resource]
    |             HTTP Request            |                                     |                                     |
    |------------------------------------>|                                     |                                     |
    |                                     |            Create Session           |                                     |
    |                                     |------------------------------------>|                                     |
    |                                     |                                     |                                     |
    |                                     |<------------------------------------|                                     |
    |                                 +---|                                     |                                     |
    |            Parse Request        |   |                                     |                                     |
    |                                 +-->|                                     |                                     |
    |                                 +---|                                     |                                     |
    |  Perform Service Authentication |   |                                     |                                     |
    |                                 +-->|                                     |                                     |
    |                                     |     Load Persistent Session Data    |                                     |
    |                                     |------------------------------------>|                                     |
    |                                     |                                     |                                     |
    |                                     |<------------------------------------|                                     |
    |                                 +---|                                     |                                     |
    |       Process Service Ruleset   |   |                                     |                                     |
    |                                 +-->|                                     |                                     |
    |                                     |                           Route Request to Resource                       |
    |                                     |-------------------------------------------------------------------------->|
    |                                     |                                     |                                 +---|
    |                                     |                                     | Perform Resource Authentication |   |
    |                                     |                                     |                                 +-->|
    |                                     |                                     |                                 +---|
    |                                     |                                     |      Process Resource Ruleset   |   |
    |                                     |                                     |                                 +-->|
    |                                     |                                     |                                 +---|
    |                                     |                                     |       Process Method Filters    |   |
    |                                     |                                     |                                 +-->|
    |                                     |                                     |                                 +---|
    |                                     |                                     |       Invoke Method Handler     |   |
    |                                     |                                     |                                 +-->|
    |                                     |                    HTTP Response    |                                     |
    |<----------------------------------------------------------------------------------------------------------------|
    |                                     |                                     |                                     |
```

Dependency Tree
---------------
```
                +----------------------------+
                |          Restbed           |
                +----------------------------+
                | Asynchronous Web Framework |
                +----------------------------+
                              |
           +------------------+------------------+
           |                  |                  |
 +--------------------+  +---------+  +----------------------+
 |        ASIO        |  | Kashmir |  |       OpenSSL        |
 +--------------------+  +---------+  +----------------------+
 | Asynchronous I/O . |  |  UUID.  |  | Secure Socket Layer. |
 +--------------------+  +---------+  +----------------------+
```

Event Loop
----------

The asynchronous nature of the framework is achieved by employing an [event-reaction loop](https://en.wikipedia.org/wiki/Event_loop), allowing Non-Block I/O and timed waits for external stimuli. This architectural decision allows the framework to scale and address the [C10K Problem](https://en.wikipedia.org/wiki/C10k_problem), all the while keeping resource consumption to a minimum and optimising thread allocation.

Thread allocation
-----------------

By default the framework will only allocate a single thread to process all incoming requests and scheduled work loads. This can be increased by altering the `Settings::set_worker_limit` attribute. It recommended that you should not exceed the available hardware limit, see below for a suggested implementation.

``` C++
#include <thread>
#include <cstdlib>
#include <restbed>

using namespace restbed;

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_worker_limit( std::thread::hardware_concurrency( ) );
    
    Service service;
    service.publish( resource );
    service.start( settings );
    
    return EXIT_SUCCESS;
}
``` 

Future Direction
----------------

 It is the aim of the core development team to remove ASIO as a dependency due to it tight coupling of IO and EventLoop principles. This setup leads to cross contamination of concerns and forces design decisions on dependees. The team will present an EventLoop offering superior handling and management of event-reaction task processing in the first quarter of 2017, and integration within Restbed before close of the same year.

 The ContextValue which provides boost::any functionality for Session state shall be replaced by std::any within the C++17 standard in future releases. If std::any is not supported a replacement drop-in shall be provided during compile time.

 WebSocketManager and ResourceCache shall be exposed for customisation by third-party developers.

 Application Layer (HTTP, HTTP2, SPDY, etc...) will be exposed for customisation by third-party developers.

 Network Layer (TCP, UDP, RS232, etc...) shall be exposed for customisation by third-party developers.

 Client functionality will be extracted from the Restbed framework, this decision has been made due to conflicting concepts for similar objects on the client/server side i.e A HTTP Session has differing properties depending on the which side of the communication channel you find yourself. Additionally this will aid in simplifying required APIs on each end, leading to a more self documenting codebase. To follow the latest progress please review the [Restless project](https://github.com/corvusoft/restless).

Further Reading
---------------

[Opaque Pointer](https://en.wikipedia.org/wiki/Opaque_pointer) - In computer programming, an opaque pointer is a special case of an opaque data type, a datatype declared to be a pointer to a record or data structure of some unspecified type.

[Uniform Resource Identifier (URI): Generic Syntax](https://tools.ietf.org/html/rfc3986) - A Uniform Resource Identifier (URI) is a compact sequence of characters that identifies an abstract or physical resource. This specification defines the generic URI syntax and a process for resolving URI references that might be in relative form, along with guidelines and security considerations for the use of URIs on the Internet. The URI syntax defines a grammar that is a superset of all valid URIs, allowing an implementation to parse the common components of a URI reference without knowing the scheme-specific requirements of every possible identifier. This specification does not define a generative grammar for URIs; that task is performed by the individual specifications of each URI scheme.

[C10K Problem](https://en.wikipedia.org/wiki/C10k_problem) - The C10K Problem refers to the inability of a server to scale beyond 10,000 connections or clients due to resource exhaustion. Servers that employ the thread-per-client model, for example, can be confounded when pooled threads spend too much time waiting on blocking operations.

[ASIO](http://think-async.com/) - Asio is a cross-platform C++ library for network and low-level I/O programming that provides developers with a consistent asynchronous model using a modern C++ approach.

[Eventloop](https://en.wikipedia.org/wiki/Event_loop) - In computer science, the event loop, message dispatcher, message loop, message pump, or run loop is a programming construct that waits for and dispatches events or messages in a program. It works by making a request to some internal or external "event provider" (that generally blocks the request until an event has arrived), and then it calls the relevant event handler ("dispatches the event"). The event-loop may be used in conjunction with a reactor, if the event provider follows the file interface, which can be selected or 'polled' (the Unix system call, not actual polling). The event loop almost always operates asynchronously with the message originator.
