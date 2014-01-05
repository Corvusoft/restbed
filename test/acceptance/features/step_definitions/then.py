# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

from lettuce import step, world

@step(u'Then I should see a status code of "([^"]*)"')
def then_i_should_see_a_status_code_of_status(step, status_code):
	assert world.service.response.status_code == int(status_code), "Status code expectation of %s does not match %s" %(status_code, world.service.response.status_code)
