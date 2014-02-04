# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

from helpers import *
from lettuce import step, world

@step(u'published a default resource$')
def published_a_default_resource(step):
	world.service.publish_default_resource()

@step(u'published a resource with "([^"]*)" response header set to "([^"]*)"$')
def published_a_resource_with_a_response_header_equal_to(step, name, value):
	world.service.publish_resource_with_response_header(name, value)

@step(u'published a resource with "([^"]*)" header filter of "([^"]*)"$')
def published_a_resource_with_a_response_header_equal_to(step, name, filter):
	if filter == "application/json":
		world.service.publish_json_resource_with_header_filter()
	elif filter == "application/xml":
		world.service.publish_xml_resource_with_header_filter()
	else:
		assert False, "Unknown resource requested"

@step(u'published a resource at "([^"]*)"$')
def i_have_published_a_resource_at_path(step, path):
	if path == "/json":
		world.service.publish_json_resource(path)
	elif path == "/xml":
		world.service.publish_xml_resource(path)
	else:
		world.service.publish_resource(path, ["GET", "PUT", "POST", "HEAD", "TRACE", "DELETE", "OPTIONS", "CONNECT" ])

@step(u'published a resource with a custom "([^"]*)" handler$')
def i_have_configured_a_service_with_a_custom_method_handler(step, method):
	if not hasattr(world, 'service') or world.service == None:
		world.service = Service(world.port)

	world.service.publish_resource("/", [method])
	