# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

from ctypes import *

library = cdll.LoadLibrary('distribution/library/libhelpers.dylib')

class Service(object):
    def __init__(self, port):
    	library.create_service.restype = c_void_p
        self.obj = library.create_service(port)

    def __del__(self):
    	library.release_service.argtypes = [c_void_p]
        library.release_service(self.obj)

    def publish_default_resource(self):
    	library.publish_default_resource.argtypes = [c_void_p]
    	library.publish_default_resource(self.obj)

    def publish_resource(self, path, method):
        library.publish_resource.argtypes = [c_void_p, c_char_p, c_char_p]
    	library.publish_resource(self.obj, path, method)

    def publish_json_resource(self, path):
        library.publish_json_resource.argtypes = [c_void_p, c_char_p]
    	library.publish_json_resource(self.obj, path)

    def publish_xml_resource(self, path):
        library.publish_xml_resource.argtypes = [c_void_p, c_char_p]
    	library.publish_xml_resource(self.obj, path)

    def publish_api_1_0_resource(self, path):
        library.publish_api_1_0_resource.argtypes = [c_void_p, c_char_p]
    	library.publish_api_1_0_resource(self.obj, path)

    def publish_api_1_1_resource(self, path):
        library.publish_api_1_1_resource.argtypes = [c_void_p, c_char_p]
    	library.publish_api_1_1_resource(self.obj, path)

    def publish_resource_with_response_header(self, name, value):
        library.publish_resource_with_response_header.argtypes = [c_void_p, c_char_p, c_char_p]
        library.publish_resource_with_response_header(self.obj, name, value)