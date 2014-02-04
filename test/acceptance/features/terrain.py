# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

import sys
import httplib2
import time

from lettuce import *
from helpers import *

@before.all
def before_all():
	sys.path.append("./features")

	world.port = 1984
	world.url = "http://localhost:" + str(world.port)

	#httplib2.debuglevel = 1 #cmd line arg

@after.each_scenario
def after_each_scenraio(scenario):
	if hasattr(world, 'service'):
		del world.service

@before.each_scenario
def before_each_scenario(scenario):
	if hasattr(world, 'http'):
		del world.http

	world.http = httplib2.Http()

#@world.absorb
#def my_project_wide_function(): username=username, password=password
    # do something
