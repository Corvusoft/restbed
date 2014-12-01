# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

import os.path
from ctypes import *
from helpers import TestService

class BasicAuthService( TestService ):
    def __init__( self, port ):
        dll_name = 'libacceptance_test_helpers.dylib'
        dll_path = os.path.dirname( os.path.abspath( __file__ ) ) + '/../../../../distribution/library/' + dll_name
        
        self.library = cdll.LoadLibrary( dll_path )
        self.library.create_authenticated_service.restype = c_void_p
        self.library.create_authenticated_service.argtypes = [ c_int ]
        
        self.obj = self.library.create_authenticated_service( port )
