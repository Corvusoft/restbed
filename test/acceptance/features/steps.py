# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

from lettuce import step, world
import base64
from helpers import *

@step(u'I have configured a service$')
def i_have_configured_a_service(step):
	if not hasattr(world, 'service') or world.service == None:
		world.service = Service(world.port)

@step(u'I have configured a Basic Auth service$')
def i_have_configured_a_basic_auth_service(step):
	if not hasattr(world, 'service') or world.service == None:
		world.service = BasicAuthService(world.port)

	world.service.publish_resource("/", ["GET", "PUT", "POST", "HEAD", "TRACE", "DELETE", "OPTIONS", "CONNECT" ])

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

@step(u'I perform a HTTP "([^"]*)" request$')
def i_perform_a_http_method_request(step, method):
	http_method = method.upper()

	headers = {'User-Agent':'acceptance tests', 'accept-encoding': 'gzip, deflate'}

	world.service.response, world.service.response.body = world.http.request(world.url, http_method, headers=headers)

@step(u'I perform a HTTP "([^"]*)" request with username "([^"]*)" and password "([^"]*)"$')
def i_perform_a_http_method_request_with_username_and_password(step, method, username, password):
	http_method = method.upper()

	authorisation = base64.encodestring( username + ':' + password )

	headers = {'User-Agent':'acceptance tests', 'accept-encoding': 'gzip, deflate', 'Authorization' : 'Basic ' + authorisation }

	world.service.response, world.service.response.body = world.http.request(world.url, http_method, headers=headers)

@step(u'I perform a HTTP "([^"]*)" request with header "([^"]*)" set to "([^"]*)"$')
def i_perform_a_http_method_request_to_path_with_header_set_to_value(step, method, header, value):
	http_method = method.upper()

	headers = {'User-Agent':'acceptance tests', 'accept-encoding': 'gzip, deflate', header:value}

	world.service.response, world.service.response.body = world.http.request(world.url, http_method, headers=headers)

@step(u'I perform a HTTP "([^"]*)" request to "([^"]*)"$')
def i_perform_a_http_method_request_to_path(step, method, path):
	http_method = method.upper()

	headers = {'User-Agent':'acceptance tests', 'accept-encoding': 'gzip, deflate'}

	url = world.url + path

	world.service.response, world.service.response.body = world.http.request(url, http_method, headers=headers)

@step(u'I should see a status code of "([^"]*)"$')
def i_should_see_a_status_code_of(step, status_code):
	assert world.service.response.status == int(status_code), "Status code expectation of %s does not match %s" %(status_code, world.service.response.status)

@step(u'I should see a "([^"]*)" response header with a value of "([^"]*)"$')
def i_should_see_a_header_value_of(step, name, value):
	header_name  = name if name in world.service.response else name.lower()
	assert header_name in world.service.response, "No '%s' header found!" % name

	header_value = world.service.response[header_name]
	assert header_value == value, "Expected %s=%s, Actual %s=%s" % (name, value, header_name, header_value)

@step(u'I should see a body of:$')
def i_should_see_a_body_of(step):
	expected = step.multiline;
	expected = unicode.replace(expected, '\n', '\r\n')
	expected += '\r\n'

	assert "".join(expected.split()) == "".join(world.service.response.body.split())
