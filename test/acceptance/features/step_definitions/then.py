# -*- coding: utf-8 -*-
# Copyright (c) 2013 Corvusoft

from lettuce import step, world

@step(u'Then I should see "([^"]*)" Incoming "([^"]*)" request 127.0.0.1')
def then_i_should_see_group1_incoming_group2_request_127_0_0_1(step, group1, group2):
    assert False, 'This step must be implemented'

@step(u'Then I should see a status code of "([^"]*)"')
def then_i_should_see_a_status_code_of_status(step, status_code):
	assert world.service.response.status_code == int(status_code), "Status code expectation of %s does not match %s" %(status_code, world.service.response.status_code)
