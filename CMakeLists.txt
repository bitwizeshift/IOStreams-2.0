cmake_minimum_required(VERSION 3.4)
project(IOStreams2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(source_files
        include/ios2/concepts/detail/void_t.hpp
        include/ios2/concepts/OStream.hpp

        include/ios2/streams/stdostream.hpp
)

add_library(ios2 ${source_files})
target_include_directories(IOStream PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include>
)