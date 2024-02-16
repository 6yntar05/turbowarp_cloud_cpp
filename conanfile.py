from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps

class turbowarp_cloud_cppRecipe(ConanFile):
    name = "turbowarp_cloud_cpp"
    version = "0.0.1"
    package_type = "application"

    # Optional metadata
    license = "MIT"
    author = "6yntar05"
    url = "https://github.com/6yntar05/turbowarp_cloud_cpp"
    description = "The turbowarp data server in C++"
    topics = ("turbowarp", "asio", "beast")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*"

    # Requires
    requires = ("boost/1.83.0", "libpqxx/7.8.1", "openssl/3.2.1")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()
        print(self.settings.compiler.cppstd)

    def configure(self):
        self.settings.compiler.cppstd = 23

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
