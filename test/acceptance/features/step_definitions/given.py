# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

from lettuce import step, world
import requests

@step(u'Given I have published a resource at "([^"]*)" with a custom "([^"]*)" handler')
def given_i_have_published_a_resource_with_a_custom_method_handler(step, path, method):
	world.service.publish_method_handler(path, method)

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

@step(u'I perform a HTTP "([^"]*)" request to "([^"]*)" with header "([^"]*)" set to "([^"]*)"')
def i_perform_a_http_request_to_path_with_header_set_to_value(step, method, path, header, value):
	verb = method.upper()
	url = world.service.url + path
	headers = {header: value}

	if verb == "GET":
		world.service.response = requests.get(url, headers=headers)
	elif verb == "PUT":
		world.service.response = requests.put(url, headers=headers)
	elif verb == "POST":
		world.service.response = requests.post(url, headers=headers)
	elif verb == "HEAD":
		world.service.response = requests.head(url, headers=headers)
	elif verb == "TRACE":
		world.service.response = requests.trace(url, headers=headers)
	elif verb == "DELETE":
		world.service.response = requests.delete(url, headers=headers)
	elif verb == "CONNECT":
		world.service.response = requests.connect(url, headers=headers)
	elif verb == "OPTIONS":
		world.service.response = requests.options(url, headers=headers)
	else:
		assert False, 'Unknown HTTP method.'

@step(u'I should see a response body of "([^"]*)"')
def i_should_see_a_response_body_of_data(step, data):
	assert world.service.response.text == data, "Expected response: " + data + " Received response: " + world.service.response.text