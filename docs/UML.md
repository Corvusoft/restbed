Overview
--------

Corvusoft's development teams frequently employ the [Unified Modelling Language](https://en.wikipedia.org/wiki/Unified_Modeling_Language) (UML) to communicate core concepts and design decisions of a system or subsystem to both technical and non-technical parties.

Among the many tools available within UML, we primarily use [Class diagrams](https://en.wikipedia.org/wiki/Class_diagram) to detail attributes, operations, and relationships. Behavioural characteristics and entity interactions are illustrated with [Sequence diagrams](https://en.wikipedia.org/wiki/Sequence_diagram).

This document outlines our interpretation of relevant UML concepts and aims to create a level playing field for all participants during software design discussions.

Interpretation
--------------

The key words “MUST”, “MUST NOT”, “REQUIRED”, “SHALL”, “SHALL NOT”, “SHOULD”, “SHOULD NOT”, “RECOMMENDED”, “MAY”, and “OPTIONAL” in this document are to be interpreted as described in [RFC 2119](http://tools.ietf.org/pdf/rfc2119.pdf).

Table of Contents
-----------------

1.	[Overview](#overview)
2.	[Interpretation](#interpretation)
3.	[Class Diagrams](#class-diagrams)
4.	[Sequence Diagrams](#sequence-diagrams)

### Class Diagrams

In software engineering, a class diagram in the Unified Modelling Language (UML) is a type of static diagram that describes the structure of a system by showing the system's classes, their attributes, operations (or methods), and the relationships among objects.

-	[Relationships](#relationships)
-	[Association](#association)
-	[Aggregation](#aggregation)
-	[Composition](#composition)
-	[Generalisation / Inheritance](#generalisation--inheritance)
-	[Realisation](#realisation)
-	[Dependency](#dependency)
-	[Stereotypes](#stereotypes)
-	[Multiplicity](#multiplicity)
-	[Visibility](#visibility)
-	[Example](#example)

#### Relationships

```
 Association:   ^   Aggregation:   O   Composition:   @   Generalisation:   #   Realisation:   :   Dependency:   _
                |                  |                  |                     |                  |                 |
              <-+->              O-+-O              @-+-@                 #-+-#              :-+-:             |-+-|
                |                  |                  |                     |                  |                 |
                V                  O                  @                     #                  :                 _
```

##### Association

Association describes logical connections or relationships between two or more entities.

##### Aggregation

Aggregation (shared association) is a variant of the "has a" association relationship; aggregation is more specific than association. It is an association that represents a part-whole or part-of relationship.

##### Composition

Composition (not-shared association) is a stronger variant of the "has a" association relationship; composition is more specific than aggregation, emphasising the dependence of the contained class on the life cycle of the container class.

##### Generalisation / Inheritance

Generalisation refers to a type of relationship wherein one associated class is a child of another by assuming the same functionalities of the parent class; in other words, the child class is a specific type of the parent class.

##### Realisation

Realisation denotes the implementation of the interface defined in one class by another class.

##### Dependency

Dependency is a unidirectional semantic relationship between two classes. It illustrates that one class relies on the functionality exported from another class.

#### Stereotypes

| \<\<Stereotype\>\>        |Description                                                                                                                                 |
|:-------------------------:|--------------------------------------------------------------------------------------------------------------------------------------------|
|          static           | Indicates an entity whose lifetime or "extent" extends across the entire run of the program.                                               |
|           class           | Represents an entity providing initial values for state and implementations of behaviour.                                                  |
|          typedef          | Used to create an alias for any other data-type. As such, it is often used to simplify the syntax of declaring complex data structures.    |
|           enum            | Enumeration stereotype shows a set of named values. The enumerator names are usually identifiers that behave as constants in the program.  |
|         interface         | Defines a contract of methods and values that implementing classes must provide.                                                           |
|         abstract          | An abstract type may provide no implementation, or an incomplete implementation; the entity cannot be instantiated directly.               |

### Multiplicity

An optional notation indicating the range of entities within a relationship.

| Notation | Description                    |
|:--------:|--------------------------------|
|   0..1   | No instances, or one instance. |
|    1     | Exactly one instance.          |
|  0..\*   | Zero or more instances.        |
|    \*    | Zero or more instances.        |
|  1..\*   | One or more instances.         |

### Visibility

It is encouraged to only show public methods, helping to reduce rework of the documentation during each software development cycle. Private, Protected, and Package visibility should only be shown when highlighting important core design decisions. For example, inheriting from a base class and altering the parent method/property visibility.


| Symbol | Description |
|:------:|-------------|
|   \+   | Public      |
|   \-   | Private     |
|   \#   | Protected   |
|   ~    | Package     |

To specify the visibility of a class member (i.e. any attributes or methods), the notation must be placed before the member's name.

#### Example

The following diagram shows that a Session class exposes two public accessor methods, and therefore is composed of a one-to-one relationship with both the Request and Response classes.

```
             +----------------------------+
             |          <<class>>         | 1
     1 +----@+           Session          +@----+
       |     |----------------------------|     |
       |     | + get_request( ) Request   |     |
       |     | + get_response( ) Response |     |
       |     +----------------------------+     |
       |                                        |
     1 |                                        | 1
+------+-------+                         +------+-------+
|   <<class>>  |                         |   <<class>>  |
|    Request   |                         |   Response   |
+--------------+                         +--------------+
```

### Sequence Diagrams

A [Sequence Diagram](https://en.wikipedia.org/wiki/Sequence_diagram) is an interaction diagram that shows how objects operate with one another and in what order. It is a construct of a [Message Sequence Chart](https://en.wikipedia.org/wiki/Message_sequence_chart). A sequence diagram shows object interactions arranged in time sequence.

#### Example

```
 [client]                                [exchange]            [formatter]         [repository]
    |                                         |                     '                    |
    |        Destroy (DELETE) resource        |                     '                    |
    |---------------------------------------->|                     '                    |
    |                                         |----------------------------------------->|
    |                                         |           Destroy resource records       |
    |           204 No Content status         |<-----------------------------------------|
    |<----------------------------------------|                     '                    |
    |                                         |                     '                    |
```
