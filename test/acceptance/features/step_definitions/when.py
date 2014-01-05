# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

from lettuce import step, world

import requests

@step(u'When I perform a HTTP "([^"]*)" request')
def when_i_perform_a_http_method_request(step, method):
	verb = method.upper()

	if verb == "GET": 
		world.service.response = requests.get('http://localhost:1984/') #world.service.url
	elif verb == "PUT":
		world.service.response = requests.put('http://localhost:1984/')
	elif verb == "POST":
		world.service.response = requests.post('http://localhost:1984/')
	elif verb == "HEAD":
		world.service.response = requests.head('http://localhost:1984/')
	elif verb == "TRACE":
		world.service.response = requests.trace('http://localhost:1984/')
	elif verb == "DELETE":
		world.service.response = requests.delete('http://localhost:1984/')
	elif verb == "CONNECT":
		world.service.response = requests.connect('http://localhost:1984/')
	elif verb == "OPTIONS":
		world.service.response = requests.options('http://localhost:1984/')
	else:
		assert False, 'Unknown HTTP method.'
