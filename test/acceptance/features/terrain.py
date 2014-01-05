# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

import sys

from lettuce import *
from helpers import *

@before.all
def before_all():
	sys.path.append("./features")

	port = 1984
	world.service = Service(port)
	world.service.url = "http://localhost:" + str(port)

@after.all
def after_all(results):
	del world.service