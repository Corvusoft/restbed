# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

from ctypes import *
from helpers import TestService

class BasicAuthService( TestService ):
    def __init__( self, port ):
    	self.library = cdll.LoadLibrary( 'distribution/library/libhelpers.dylib' )
    	self.library.create_authenticated_service.restype = c_void_p
    	self.library.create_authenticated_service.argtypes = [ c_int ]
		
        self.obj = self.library.create_authenticated_service( port )
