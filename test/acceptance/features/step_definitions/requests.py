# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

from helpers import *
from lettuce import step, world


@step( u'I perform a HTTP "([^"]*)" request$' )
def i_perform_a_http_method_request( step, method ):
	world.response = world.perform_http_request( method = method )


@step( u'I perform a HTTP "([^"]*)" request with username "([^"]*)" and password "([^"]*)"$' )
def i_perform_a_http_method_request_with_username_and_password( step, method, username, password ):
	world.response = world.perform_http_request( method = method, username = username, password = password )


@step( u'I perform a HTTP "([^"]*)" request with header "([^"]*)" set to "([^"]*)"$' )
def i_perform_a_http_method_request_to_path_with_header_set_to_value( step, method, header, value ):
	headers = { header : value }

	world.response = world.perform_http_request( method = method, headers = { header : value } )


@step( u'I perform a HTTP "([^"]*)" request to "([^"]*)"$' )
def i_perform_a_http_method_request_to_path( step, method, path ):
	url = world.url + path

	world.response = world.perform_http_request( url, method )
