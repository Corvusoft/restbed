/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include <corvusoft/restbed/rule.hpp>
#include <corvusoft/restbed/session.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::function;
using std::shared_ptr;

//Project Namespaces
using restbed::Rule;
using restbed::Bytes;
using restbed::Session;

//External Namespaces

class TestRule : public Rule
{
	public:
		TestRule( void ) : Rule( )
		{
			return;
		}

		TestRule( const Type type ) : Rule( type )
		{
			return;
		}

		TestRule( const TestRule& original ) : Rule( original )
		{
			return;
		}

		~TestRule( void )
		{
			return;
		}

	    virtual bool condition( const Bytes& )
	    {
	    	return true;
	    }

	    virtual void action( const shared_ptr< Session >& session, function< void ( const shared_ptr< Session >& ) >& callback )
	    {
	    	callback( session );
	    }
};

TEST_CASE( "validate default instance values", "[rule]" )
{
    const TestRule rule;

    REQUIRE( rule.get_type( ) == Rule::ALL );
    REQUIRE( rule.get_priority( ) == 0 );
    REQUIRE( rule.is_mandatory( ) == false );
}

TEST_CASE( "confirm default destructor throws no exceptions", "[rule]" )
{
    auto rule = new TestRule;

    REQUIRE_NOTHROW( delete rule );
}

TEST_CASE( "validate setters modify default values", "[rule]" )
{
	TestRule rule( Rule::HEADER );
	rule.set_priority( 33 );
	rule.set_mandatory( true );

    REQUIRE( rule.get_type( ) == Rule::HEADER );
    REQUIRE( rule.get_priority( ) == 33 );
    REQUIRE( rule.is_mandatory( ) == true );
}

TEST_CASE( "validate copy constructor", "[rule]" )
{
	TestRule original( Rule::HEADER );
	original.set_priority( 33 );
	original.set_mandatory( true );

	const TestRule copy( original );

    REQUIRE( copy.get_type( ) == Rule::HEADER );
    REQUIRE( copy.get_priority( ) == 33 );
    REQUIRE( copy.is_mandatory( ) == true );
}

TEST_CASE( "validate assignment constructor", "[rule]" )
{
	TestRule original( Rule::HEADER );
	original.set_priority( 33 );
	original.set_mandatory( true );

	const TestRule copy = original;

    REQUIRE( copy.get_type( ) == Rule::HEADER );
    REQUIRE( copy.get_priority( ) == 33 );
    REQUIRE( copy.is_mandatory( ) == true );
}

TEST_CASE( "validate less-then operator", "[rule]" )
{
	TestRule lhs( Rule::HEADER );
	lhs.set_priority( 1 );

	TestRule rhs( Rule::HEADER );
	rhs.set_priority( 3 );

    REQUIRE( lhs < rhs );
}

TEST_CASE( "validate greater-then operator", "[rule]" )
{
	TestRule lhs( Rule::HEADER );
	lhs.set_priority( 3 );

	TestRule rhs( Rule::HEADER );
	rhs.set_priority( 1 );

    REQUIRE( lhs > rhs );
}

TEST_CASE( "validate equality operator", "[rule]" )
{
	TestRule lhs( Rule::HEADER );
	lhs.set_priority( 33 );
	lhs.set_mandatory( true );

	TestRule rhs( Rule::HEADER );
	rhs.set_priority( 33 );
	rhs.set_mandatory( true );

    REQUIRE( lhs == rhs );
}

TEST_CASE( "validate inequality operator", "[rule]" )
{
	TestRule lhs( Rule::HEADER );
	lhs.set_priority( 2 );
	lhs.set_mandatory( false );

	TestRule rhs( Rule::QUERY );
	rhs.set_priority( 33 );
	rhs.set_mandatory( true );

    REQUIRE( lhs not_eq rhs );
}
