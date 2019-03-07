if (MSVC)
    #set(YAMLCPP_LIBRARY "")
	find_package(yaml-cpp CONFIG REQUIRED)
else ()
    find_package(yaml-cpp REQUIRED)
endif ()

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_Package(Freetype REQUIRED)

add_subdirectory(tools)
add_subdirectory(cmd)
add_subdirectory(editor)
add_subdirectory(runner)
