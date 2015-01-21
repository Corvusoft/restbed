# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014, 2015 Corvusoft

from helpers import *
from lettuce import step, world

@step( u'then suppress the resource$' )
def and_i_then_suppress_the_resource( step ):
    world.service.suppress_resource( )
