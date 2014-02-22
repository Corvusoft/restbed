# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

from helpers import *
from lettuce import step, world

@step( u'published a default resource$' )
def published_a_default_resource( step ):
	world.service.publish_resource( )

@step( u'published a resource with "([^"]*)" response header set to "([^"]*)"$' )
def published_a_resource_with_a_response_header_equal_to( step, header, value ):
	world.service.publish_resource( "/", [ "GET", "PUT", "POST", "HEAD", "TRACE", "DELETE", "OPTIONS", "CONNECT" ], header, value )

@step( u'published a JSON resource with "([^"]*)" header filter of "([^"]*)"$' )
def published_a_json_resource_with_a_response_header_equal_to( step, header, filter ):
	world.service.publish_json_resource( "/", header, filter )

@step( u'published a XML resource with "([^"]*)" header filter of "([^"]*)"$' )
def published_a_xml_resource_with_a_response_header_equal_to( step, header, filter ):
	world.service.publish_xml_resource( "/", header, filter )

@step( u'published a resource at "([^"]*)"$' )
def published_a_resource_at_path( step, path ):
		world.service.publish_resource( path, [ "GET", "PUT", "POST", "HEAD", "TRACE", "DELETE", "OPTIONS", "CONNECT" ] )

@step( u'published a JSON resource at "([^"]*)"$' )
def published_a_resource_at_path( step, path ):
		world.service.publish_json_resource( path )

@step( u'published a XML resource at "([^"]*)"$' )
def published_a_resource_at_path( step, path ):
		world.service.publish_xml_resource( path )

@step( u'published a resource with a custom "([^"]*)" handler$' )
def published_a_resource_with_a_custom_handler( step, method ):
	world.service.publish_resource( "/", [ method ] )
