# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

from lettuce import step, world

import httplib2

@step(u'I perform a HTTP "([^"]*)" request')
def i_perform_a_http_method_request(step, method):
	verb = method.upper()
	url = world.service.url

	http = httplib2.Http()

	if verb == "GET":
		world.service.response, world.service.response.body = http.request(url, "GET", headers={'User-Agent':'acceptance tests', 'accept-encoding': 'gzip, deflate'})
	elif verb == "PUT":
		world.service.response, world.service.response.body = http.request(url, "PUT", headers={'User-Agent':'acceptance tests', 'accept-encoding': 'gzip, deflate'})
	elif verb == "POST":
		world.service.response, world.service.response.body = http.request(url, "POST", headers={'User-Agent':'acceptance tests', 'accept-encoding': 'gzip, deflate'})
	elif verb == "HEAD":
		world.service.response, world.service.response.body = http.request(url, "HEAD", headers={'User-Agent':'acceptance tests', 'accept-encoding': 'gzip, deflate'})
	elif verb == "TRACE":
		world.service.response, world.service.response.body = http.request(url, "TRACE", headers={'User-Agent':'acceptance tests', 'accept-encoding': 'gzip, deflate'})
	elif verb == "DELETE":
		world.service.response, world.service.response.body = http.request(url, "DELETE", headers={'User-Agent':'acceptance tests', 'accept-encoding': 'gzip, deflate'})
	elif verb == "OPTIONS":
		world.service.response, world.service.response.body = http.request(url, "OPTIONS", headers={'User-Agent':'acceptance tests', 'accept-encoding': 'gzip, deflate'})
	elif verb == "CONNECT":
		world.service.response, world.service.response.body = http.request(url, "CONNECT", headers={'User-Agent':'acceptance tests', 'accept-encoding': 'gzip, deflate'})
	else:
		assert False, 'Unknown HTTP method.'
