from conans import ConanFile, CMake, tools
import os


class RestbedConan(ConanFile):
    name = "restbed"
    version = "4.5-RC1"
    license = "AGPL"
    url = "https://github.com/Corvusoft/restbed"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "examples": [True, False],
        "tests": [True, False],
        "ssl": [True, False]
    }
    default_options =\
        "shared=False",\
        "examples=False", \
        "tests=False", \
        "ssl=True"
        generators = "cmake"

    def source(self):
        self.run("git clone https://github.com/Corvusoft/restbed.git")
        self.run("cd restbed")

    def build(self):
        cmake = CMake(self.settings)
        flags = "-DBUILD_SHARED=ON" if self.options.shared else ""
        flags += "-DBUILD_EXAMPLES=ON" if self.options.examples else ""
        flags += "-DBUILD_TESTS=ON" if self.options.tests else ""
        flags += "-DBUILD_SSL=ON" if self.options.ssl else ""
        self.run('cmake restbed %s %s' % (cmake.command_line, flags))
        self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.h", dst="include", src="restbed")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["restbed"]
