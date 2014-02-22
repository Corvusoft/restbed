# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

from helpers import *
from lettuce import step, world

@step( u'publish a default resource$' )
def publish_a_default_resource( step ):
	world.service.publish_resource( )

@step( u'publish a resource with "([^"]*)" response header set to "([^"]*)"$' )
def publish_a_resource_with_a_response_header_equal_to( step, header, value ):
	world.service.publish_resource( "/", [ "GET", "PUT", "POST", "HEAD", "TRACE", "DELETE", "OPTIONS", "CONNECT" ], header, value )

@step( u'publish a JSON resource with "([^"]*)" header filter of "([^"]*)"$' )
def publish_a_json_resource_with_a_response_header_equal_to( step, header, filter ):
	world.service.publish_json_resource( "/", header, filter )

@step( u'publish a XML resource with "([^"]*)" header filter of "([^"]*)"$' )
def publish_a_xml_resource_with_a_response_header_equal_to( step, header, filter ):
	world.service.publish_xml_resource( "/", header, filter )

@step( u'publish a resource at "([^"]*)"$' )
def publish_a_resource_at_path( step, path ):
		world.service.publish_resource( path, [ "GET", "PUT", "POST", "HEAD", "TRACE", "DELETE", "OPTIONS", "CONNECT" ] )

@step( u'publish a JSON resource at "([^"]*)"$' )
def publish_a_resource_at_path( step, path ):
		world.service.publish_json_resource( path )

@step( u'publish a XML resource at "([^"]*)"$' )
def publish_a_resource_at_path( step, path ):
		world.service.publish_xml_resource( path )

@step( u'publish a resource with a custom "([^"]*)" handler$' )
def publish_a_resource_with_a_custom_handler( step, method ):
	world.service.publish_resource( "/", [ method ] )
