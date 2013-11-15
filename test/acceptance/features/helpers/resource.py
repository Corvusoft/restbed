from ctypes import *

library = cdll.LoadLibrary('./libhelpers.so')

prototype = CFUNCTYPE(None, c_int)

class Foo(object):
    def __init__(self):
        self.obj = library.Foo_new()

    def bar(self):
        library.Foo_bar(self.obj)

    def call(self, func):
    	callback = prototype(func)
    	library.Foo_call(callback)