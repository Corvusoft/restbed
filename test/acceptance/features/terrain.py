# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

import sys

from lettuce import *
from helpers import *

@before.all
def before_all():
	sys.path.append("./features")
	world.service = Service(1984)

@after.all
def after_all(results):
	del world.service