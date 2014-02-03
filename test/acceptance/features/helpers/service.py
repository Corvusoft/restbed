# -*- coding: utf-8 -*-
# Copyright (c) 2013, 2014 Corvusoft

from ctypes import *

library = cdll.LoadLibrary('distribution/library/libhelpers.dylib')

library.create_service.restype = c_void_p
library.create_service.argtypes = [c_int]

class Service(object):
    def __init__(self, port):
        self.obj = library.create_service(port)

    def __del__(self):
    	library.release_service.argtypes = [c_void_p]
        library.release_service(self.obj)

    def publish_default_resource(self):
    	library.publish_default_resource.argtypes = [c_void_p]
    	library.publish_default_resource(self.obj)

    def publish_resource(self, path, methods):
        length = len(methods)

        methods_type = (c_char_p * length)
        argument = methods_type()

        for key, item in enumerate(methods):
            argument[key] = item

        library.publish_resource.argtypes = [c_void_p, c_char_p, methods_type]

    	library.publish_resource(self.obj, path, argument)

    def publish_json_resource(self, path):
        library.publish_json_resource.argtypes = [c_void_p, c_char_p]
        library.publish_json_resource(self.obj, path)

    def publish_xml_resource(self, path):
        library.publish_xml_resource.argtypes = [c_void_p, c_char_p]
        library.publish_xml_resource(self.obj, path)

    def publish_json_resource_with_header_filter(self):
        library.publish_json_resource_with_header_filter.argtypes = [c_void_p]
    	library.publish_json_resource_with_header_filter(self.obj)

    def publish_xml_resource_with_header_filter(self):
        library.publish_xml_resource_with_header_filter.argtypes = [c_void_p]
    	library.publish_xml_resource_with_header_filter(self.obj)

    def publish_resource_with_response_header(self, name, value):
        library.publish_resource_with_response_header.argtypes = [c_void_p, c_char_p, c_char_p]
        library.publish_resource_with_response_header(self.obj, name, value)
