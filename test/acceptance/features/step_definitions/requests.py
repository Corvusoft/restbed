# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

from helpers import *
from lettuce import step, world

import base64

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
	