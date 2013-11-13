# -*- coding: utf-8 -*-
from lettuce import step

@step(u'When I perform an authorised HTTP "([^"]*)"" request')
def when_i_perform_an_authorised_http_group1_request(step, group1):
    assert False, 'This step must be implemented'

@step(u'When I perform an unauthorised HTTP "([^"]*)" request')
def when_i_perform_an_unauthorised_http_group1_request(step, group1):
    assert False, 'This step must be implemented'

@step(u'When I perform a HTTP "([^"]*)" request')
def when_i_perform_a_http_group1_request(step, group1):
    assert False, 'This step must be implemented'

@step(u'When I perform HTTP "([^"]*)" requests')
def when_i_perform_http_group1_requests(step, group1):
    assert False, 'This step must be implemented'

@step(u'When I perform a HTTP OPTIONS request')
def when_i_perform_a_http_options_request(step):
    assert False, 'This step must be implemented'

@step(u'When I perform a HTTP TRACE request')
def when_i_perform_a_http_trace_request(step):
    assert False, 'This step must be implemented'
