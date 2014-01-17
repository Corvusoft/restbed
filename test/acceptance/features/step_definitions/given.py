# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

from lettuce import step, world
import httplib2

@step(u'I have published a resource with a custom "([^"]*)" handler')
def i_have_published_a_resource_with_a_custom_method_handler(step, method):
	world.service.publish_resource("/", method)

@step(u'I have published a resource at "([^"]*)" with a custom "([^"]*)" handler')
def i_have_published_a_resource_with_a_custom_method_handler(step, path, method):
	world.service.publish_resource(path, method)

@step(u'I have published a resource at "([^"]*)" with a "([^"]*)" header filter of "([^"]*)"')
def i_have_published_a_resource_at_path_with_a_header_filter_of_value(step, path, header, value):
	if value == "application/json":
		world.service.publish_json_resource(path)
	elif value == "application/xml":
		world.service.publish_xml_resource(path)
	elif value == "1.0":
		world.service.publish_api_1_0_resource(path)
	elif value == "1.1":
		world.service.publish_api_1_1_resource(path)
	else:
		assert False, "Unknown resource requested"

@step(u'I have published a custom resource with response header "([^"]*)" and a value of "([^"]*)"')
def i_have_published_a_custom_resource_with_response_header_name_and_a_value_of_value(step, name, value):
    world.service.publish_resource_with_response_header(name, value)

@step(u'I perform a HTTP "([^"]*)" request to "([^"]*)" with header "([^"]*)" set to "([^"]*)"')
def i_perform_a_http_request_to_path_with_header_set_to_value(step, method, path, header, value):
	verb = method.upper()
	url = world.service.url + path

	http = httplib2.Http()

	if verb == "GET":
		world.service.response, world.service.response.body = http.request(url, "GET", headers={'User-Agent':'acceptance tests', 'accept-encoding': 'gzip, deflate', header:value} )
	elif verb == "PUT":
		world.service.response, world.service.response.body = http.request(url, "PUT", headers={'User-Agent':'acceptance tests', 'accept-encoding': 'gzip, deflate', header:value} )
	elif verb == "POST":
		world.service.response, world.service.response.body = http.request(url, "POST", headers={'User-Agent':'acceptance tests', 'accept-encoding': 'gzip, deflate', header:value} )
	elif verb == "HEAD":
		world.service.response, world.service.response.body = http.request(url, "HEAD", headers={'User-Agent':'acceptance tests', 'accept-encoding': 'gzip, deflate', header:value} )
	elif verb == "TRACE":
		world.service.response, world.service.response.body = http.request(url, "TRACE", headers={'User-Agent':'acceptance tests', 'accept-encoding': 'gzip, deflate', header:value} )
	elif verb == "DELETE":
		world.service.response, world.service.response.body = http.request(url, "DELETE", headers={'User-Agent':'acceptance tests', 'accept-encoding': 'gzip, deflate', header:value} )
	elif verb == "OPTIONS":
		world.service.response, world.service.response.body = http.request(url, "OPTIONS", headers={'User-Agent':'acceptance tests', 'accept-encoding': 'gzip, deflate', header:value} )
	elif verb == "CONNECT":
		world.service.response, world.service.response.body = http.request(url, "CONNECT", headers={'User-Agent':'acceptance tests', 'accept-encoding': 'gzip, deflate', header:value} )
	else:
		assert False, 'Unknown HTTP method.'


@step(u'I should see a response body of "([^"]*)"')
def i_should_see_a_response_body_of_data(step, data):
	assert world.service.response.body == data, "Expected response: " + data + " Received response: " + world.service.response.body

@step(u'I have published a default resource')
def i_have_published_a_default_resource(step):
    world.service.publish_default_resource()

@step(u'I should see a "([^"]*)" response header with a value of "([^"]*)"')
def i_should_see_a_header_value_of(step, name, value):
	header  = name if world.service.response.has_key(name) else name.lower()
	assert world.service.response[header] == value, "Expected " + name + " header value of " + value

@step(u'I should see a body of:')
def and_i_should_see_a_body_of(step):
	expected = step.multiline;
	expected = unicode.replace(expected, '\n', '\r\n')
	expected += '\r\n'

	assert expected == world.service.response.body