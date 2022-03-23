file(GLOB lib_srcs "*.cpp")
list(FILTER lib_srcs EXCLUDE REGEX ".*main\\.cpp$")

add_library(island-lib ${lib_srcs})
