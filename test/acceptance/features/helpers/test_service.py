# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

import os.path
from ctypes import *

class TestService( object ):
    def __init__( self, port ):
        dll_name = 'libacceptance_test_helpers.dylib'
        dll_path = os.path.dirname( os.path.abspath( __file__ ) ) + '/../../../../distribution/library/' + dll_name
        
        self.library = cdll.LoadLibrary( dll_path )
        self.library.create_service.restype = c_void_p
        self.library.create_service.argtypes = [ c_int ]

        self.obj = self.library.create_service( port )

    def __del__( self ):
    	self.library.release_service.argtypes = [ c_void_p ]
        self.library.release_service( self.obj )
        
    def get_log_entry( self ):
        self.library.get_log_entry.restype = c_char_p
        self.library.get_log_entry.argtypes = [ c_void_p ]

        return self.library.get_log_entry( self.obj )

    def suppress_resource( self ):
        self.library.suppress_resource.argtypes = [ c_void_p ]
        self.library.suppress_resource( self.obj )

    def publish_resource( self, path = "/", methods = [ ], header = None, value = None ):
        length = len( methods )

        methods_type = ( c_char_p * length )
        argument = methods_type( )

        for key, item in enumerate( methods ):
            argument[key] = item

        self.library.publish_resource.argtypes = [ c_void_p, c_char_p, methods_type, c_char_p, c_char_p ]
    	self.library.publish_resource( self.obj, path, argument, header, value )

    def publish_json_resource( self, path, header = None, filter = None ):
        self.library.publish_json_resource.argtypes = [ c_void_p, c_char_p, c_char_p, c_char_p ]
        self.library.publish_json_resource( self.obj, path, header, filter )

    def publish_xml_resource( self, path, header = None, filter = None ):
        self.library.publish_xml_resource.argtypes = [ c_void_p, c_char_p, c_char_p, c_char_p ]
        self.library.publish_xml_resource( self.obj, path, header, filter )
