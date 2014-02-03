# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

from ctypes import *
from helpers import Service

library = cdll.LoadLibrary('distribution/library/libhelpers.dylib')

library.create_authenticated_service.restype = c_void_p
library.create_authenticated_service.argtypes = [c_int]

class BasicAuthService(Service):
    def __init__(self, port):
        self.obj = library.create_authenticated_service(port)
