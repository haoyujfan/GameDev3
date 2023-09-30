#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

if env["platform"] == "macos":
    library1 = env.SharedLibrary(
        "Assignment2/bin/libplayer.{}.{}.framework/libplayer.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    ),
    library2 = env.SharedLibrary(
    "Assignment2/bin/libfood.{}.{}.framework/libplayer.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    ),
    library3 = env.SharedLibrary(
        "Assignment2/bin/libcamera.{}.{}.framework/libplayer.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    ),
    library4 = env.SharedLibrary(
        "Assignment2/bin/libground.{}.{}.framework/libplayer.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    ),    
    library5 = env.SharedLibrary(
        "Assignment2/bin/libcactus.{}.{}.framework/libplayer.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )

else:
    library1 = env.SharedLibrary(
        "Assignment2/bin/libplayer{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    ),
    library2 = env.SharedLibrary(
        "Assignment2/bin/libfood{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    ),
    library3 = env.SharedLibrary(
        "Assignment2/bin/libcamera{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    ),
    library4 = env.SharedLibrary(
        "Assignment2/bin/libground{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    ),
    library5 = env.SharedLibrary(
        "Assignment2/bin/libcactus{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library1)
Default(library2)
Default(library3)
Default(library4)
Default(library5)
