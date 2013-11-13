# -*- coding: utf-8 -*-
from lettuce import step

@step(u'Then I should see a status code of 200')
def then_i_should_see_a_status_code_of_200(step):
    assert False, 'This step must be implemented'

@step(u'Then I should see a status code of 401')
def then_i_should_see_a_status_code_of_401(step):
    assert False, 'This step must be implemented'

@step(u'Then I should see "([^"]*)" Incoming "([^"]*)" request 127.0.0.1')
def then_i_should_see_group1_incoming_group2_request_127_0_0_1(step, group1, group2):
    assert False, 'This step must be implemented'

@step(u'Then I should see a status code of "([^"]*)"')
def then_i_should_see_a_status_code_of_group1(step, group1):
    assert False, 'This step must be implemented'
