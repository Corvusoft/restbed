# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

from helpers import *
from lettuce import step, world

@step( u'I should see a status code of "([^"]*)"$' )
def i_should_see_a_status_code_of( step, status_code ):
	assert int( world.response.status ) == int( status_code ), "Status code expectation of %s does not match %s" %( status_code, world.response.status )

@step( u'I should see a "([^"]*)" response header with a value of "([^"]*)"$' )
def i_should_see_a_header_value_of( step, name, value ):
	header_name  = name if name in world.response.headers else name.lower( )
	assert header_name in world.response.headers, "No '%s' header found!" % name

	header_value = world.response.headers[ header_name ]
	assert header_value == value, "Expected %s=%s, Actual %s=%s" % ( name, value, header_name, header_value )

@step( u'I should see a body of:$' )
def i_should_see_a_body_of( step ):
	expected = step.multiline;
	expected = unicode.replace( expected, '\n', '\r\n' )
	expected += '\r\n'

	assert "".join( expected.split( ) ) == "".join( world.response.body.split( ) )

@step( u'I should see a log entry of "([^"]*)"$' )
def i_should_see_a_log_entry_of( step, expectation ):
    if "::1" in expectation:
    	expectation = expectation.replace( "::1", "" )
        
    	actual = world.service.get_log_entry( ).replace( "::1", "" )
    	actual = actual.replace( "127.0.0.1", "" )
    	actual = actual.replace( "::ffff:127.0.0.1", "" )

	assert actual == expectation, "Failed to find matching log entry"
