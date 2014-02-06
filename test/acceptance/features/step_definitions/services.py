# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

from helpers import *
from lettuce import step, world


@step( u'I have configured a service$' )
def i_have_configured_a_service( step ):
	if not hasattr( world, 'service' ) or world.service == None:
		world.service = Service( world.port )


@step( u'I have configured a Basic Auth service$' )
def i_have_configured_a_basic_auth_service( step ):
	if not hasattr( world, 'service' ) or world.service == None:
		world.service = BasicAuthService( world.port )

	world.service.publish_resource( "/", [ "GET", "PUT", "POST", "HEAD", "TRACE", "DELETE", "OPTIONS", "CONNECT" ] )
