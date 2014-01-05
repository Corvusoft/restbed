# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

from lettuce import step, world

import requests

@step(u'When I perform a HTTP "([^"]*)" request')
def when_i_perform_a_http_method_request(step, method):
	verb = method.upper()
	url = world.service.url

	if verb == "GET":
		world.service.response = requests.get(url)
	elif verb == "PUT":
		world.service.response = requests.put(url)
	elif verb == "POST":
		world.service.response = requests.post(url)
	elif verb == "HEAD":
		world.service.response = requests.head(url)
	elif verb == "DELETE":
		world.service.response = requests.delete(url)
	elif verb == "OPTIONS":
		world.service.response = requests.options(url)
	else:
		assert False, 'Unknown HTTP method.'
