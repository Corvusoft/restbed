from ctypes import *

library = cdll.LoadLibrary('distribution/library/libhelpers.dylib')

prototype = CFUNCTYPE(None, c_char_p)

class Foo(object):
    def __init__(self):
        self.obj = library.Foo_new()

    def bar(self):
        library.Foo_bar(self.obj)

    def call(self, func):
    	callback = prototype(func)
    	library.Foo_call(callback)