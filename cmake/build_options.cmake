# Common build options/warnings I like to use, kept in a separate file for
# portability
# General
add_definitions("-g -pthread -O2 -Wall -Wextra -Wpedantic")
# Better warnings
# printf/scanf first arg must be a string literal
add_definitions("-Wformat-nonliteral")
# Warn if a cast discards a qualifier, such as const
add_definitions("-Wcast-qual")
# Warn on implicit conversions they may change the value e.g. int(2.1f)
add_definitions("-Wconversion")
# Warns if there is code that can never be executed
add_definitions("-Wunreachable-code")
# Warns if all enum options aren't accounted for in switch() statements
add_definitions("-Wswitch-enum")
# Warns if there is a switch() fallthrough without using [[fallthrough]]
add_definitions("-Wimplicit-fallthrough")
# Warns if you try to compare floating point types with == or !=
add_definitions("-Wfloat-equal")
