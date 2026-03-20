import os
import re

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy, load


class NumopsConan(ConanFile):
    """Conan 2 recipe for the numops C++ arithmetic library."""

    name = "numops"
    license = "MIT"
    url = "https://github.com/skolobov/curly-enigma"
    description = "A small C++ arithmetic library"
    topics = ("arithmetic", "math", "library")

    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    exports_sources = (
        "CMakeLists.txt",
        "cmake/*",
        "include/*",
        "src/*",
    )

    def set_version(self):
        """Read version from CMakeLists.txt unless overridden via --version."""
        if self.version:
            return
        content = load(self, os.path.join(self.recipe_folder, "CMakeLists.txt"))
        match = re.search(r"project\(\s*numops\s+VERSION\s+(\d+\.\d+\.\d+)", content)
        if match:
            self.version = match.group(1)

    def config_options(self):
        """Remove fPIC option on Windows."""
        if self.settings.os == "Windows":
            del self.options.fPIC

    def configure(self):
        """Remove fPIC when building shared libraries."""
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        """Use standard CMake layout."""
        cmake_layout(self)

    def generate(self):
        """Generate CMake toolchain with testing disabled."""
        tc = CMakeToolchain(self)
        tc.variables["BUILD_TESTING"] = False
        tc.generate()

    def build(self):
        """Configure and build the library with CMake."""
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        """Install headers, library, and license into the package folder."""
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        """Define library name and CMake target information for consumers."""
        self.cpp_info.libs = ["numops"]
        self.cpp_info.set_property("cmake_file_name", "numops")
        self.cpp_info.set_property("cmake_target_name", "numops::numops")
