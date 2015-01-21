# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014, 2015 Corvusoft

import sys
import base64
import httplib2

from lettuce import *
from helpers import *

@before.all
def before_all( ):
	world.port = 1984
	world.url = "http://localhost:" + str( world.port )

@after.each_scenario
def after_each_scenraio( scenario ):
	if hasattr( world, 'service' ):
		del world.service

@before.each_scenario
def before_each_scenario( scenario ):
	if hasattr( world, 'http' ):
		del world.http

	world.http = httplib2.Http( )

@world.absorb
def perform_http_request( url = None, method = "GET", body = None, headers = None, username = None, password = None ):
	request_url = build_url( url )
	request_method = build_method( method )
	request_headers = build_headers( headers, username, password )

	http = httplib2.Http( )
	
	response_headers, response_body = http.request( request_url, request_method, headers = request_headers )

	return type( "Response", ( object, ), dict( status = response_headers[ "status" ], headers = response_headers, body = response_body ) )

def build_url( url ):
	request_url = None

	if url == None:
		request_url = world.url
	else:
		request_url = url

	return request_url

def build_method( method ):
	return method.upper( )

def build_headers( headers, username, password ):
	request_headers = { "User-Agent": "Restbed Acceptance Tests", "accept-encoding": "gzip, deflate" };

	if headers != None:
		request_headers = dict( request_headers.items( ) + headers.items( ) )

	if username != None or password != None:
		header = build_basic_auth_header( username, password )

		request_headers = dict( request_headers.items( ) + header.items( ) )

	return request_headers

def build_basic_auth_header( username, password ):
	authorisation = base64.encodestring( username + ':' + password )

	return { 'Authorization' : 'Basic ' + authorisation }
