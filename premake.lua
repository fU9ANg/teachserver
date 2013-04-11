solution "server-solution"
    configurations { "Debug", "Release" }

    porject "server"
    language "C++"
    files { "**.h", "**.cpp" }

    language "C"
    files { "**.c" }

    configuration "Debug"
        defines { "DEBUG" }
        flags { "-O0 -Wall -Werror -g " }

    configuration "Release"
        defines { "RELEASE" }
        flags { "-O0 -Wall -Werror "}
