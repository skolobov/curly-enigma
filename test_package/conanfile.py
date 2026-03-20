import os

from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.build import can_run


class NumopsTestConan(ConanFile):
    """Consumer project that validates the numops Conan package."""

    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        """Declare the package under test as a dependency."""
        self.requires(self.tested_reference_str)

    def layout(self):
        """Use standard CMake layout."""
        cmake_layout(self)

    def build(self):
        """Configure and build the consumer project."""
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        """Run the consumer executable to validate library functionality."""
        if can_run(self):
            cmd = os.path.join(self.cpp.build.bindir, "example")
            self.run(cmd, env="conanrun")
