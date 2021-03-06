cmake_minimum_required(VERSION 3.9)
set(CMAKE_MACOSX_RPATH 1)
project(Unisparks)

set(LIB_SOURCES 
	unisparks.hpp
	unisparks/effects/pixeltest.hpp
	unisparks/effects/scrolltext.hpp
	unisparks/networks/udp.cpp
	unisparks/networks/udp.hpp
	unisparks/renderers/opengl.hpp
	unisparks/util/geom3d.hpp
	unisparks/util/log.cpp
	unisparks/util/time.cpp
	../src/unisparks/effect.hpp
	../src/unisparks/effects/chess.hpp
	../src/unisparks/effects/flame.cpp
	../src/unisparks/effects/flame.hpp
	../src/unisparks/effects/functional.hpp
	../src/unisparks/effects/glitter.hpp
	../src/unisparks/effects/overlay.hpp
	../src/unisparks/effects/plasma.hpp
	../src/unisparks/effects/rainbow.hpp
	../src/unisparks/effects/rider.hpp
	../src/unisparks/effects/scroll.hpp
	../src/unisparks/effects/sequence.hpp
	../src/unisparks/effects/slantbars.hpp
	../src/unisparks/effects/solid.hpp
	../src/unisparks/effects/transform.hpp
	../src/unisparks/effects/treesine.hpp
	../src/unisparks/frame.cpp
	../src/unisparks/frame.hpp
	../src/unisparks/layout.hpp
	../src/unisparks/layouts/matrix.hpp
	../src/unisparks/layouts/pixelmap.hpp
	../src/unisparks/layouts/reversemap.hpp
	../src/unisparks/layouts/transformed.hpp
	../src/unisparks/network.cpp
	../src/unisparks/network.hpp
	../src/unisparks/player.cpp
	../src/unisparks/player.hpp
	../src/unisparks/renderer.hpp
	../src/unisparks/renderers/simple.hpp
	../src/unisparks/util/color.cpp
	../src/unisparks/util/color.hpp
	../src/unisparks/util/geom.hpp
	../src/unisparks/util/log.cpp
	../src/unisparks/util/log.hpp
	../src/unisparks/util/math.cpp
	../src/unisparks/util/math.hpp
	../src/unisparks/util/meta.hpp
	../src/unisparks/util/new.hpp
	../src/unisparks/util/rhytm.hpp
	../src/unisparks/util/stream.hpp
	../src/unisparks/util/time.hpp
)

set(DEMO_SOURCES 
	demo/main.cpp 
	demo/overlays.cpp 
	unisparks/effects/scrolltext.hpp
)

set(TEST_SOURCES 
	tests/main.cpp
	tests/player.cpp
)

set(BENCH_SOURCES 
	bench/main.cpp
)

# LIBRARY
add_library(unisparks STATIC ${LIB_SOURCES})
target_include_directories(unisparks PUBLIC ../src .)
set_target_properties(unisparks PROPERTIES COMPILE_OPTIONS "-std=c++11" "-fPIC" "-Wall" "-Wextra" "-Werror")
install(TARGETS unisparks LIBRARY ARCHIVE DESTINATION lib)
install(DIRECTORY src/ COMPONENT "lib" DESTINATION include FILES_MATCHING PATTERN "*.h" PATTERN "Unisparks.h" EXCLUDE)
install(DIRECTORY extras/unisparks/ COMPONENT "lib" DESTINATION include/unisparks FILES_MATCHING PATTERN "*.h")

# DEMO
find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)
add_executable(unisparks-demo ${DEMO_SOURCES})
target_link_libraries(unisparks-demo unisparks glfw ${OPENGL_gl_LIBRARY})
target_include_directories(unisparks-demo PRIVATE ../src ${GLFW_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
set_target_properties(unisparks-demo PROPERTIES COMPILE_OPTIONS "-std=c++14" "-fPIC" "-Wall" "-Wextra" "-Werror")
install(TARGETS unisparks-demo DESTINATION bin COMPONENT "demo")

# TESTS
add_executable(unisparks-test ${TEST_SOURCES})
target_link_libraries(unisparks-test unisparks)
target_include_directories(unisparks-test PRIVATE tests)
set_target_properties(unisparks-test PROPERTIES COMPILE_OPTIONS "-std=c++14" "-fPIC" "-Wall" "-Wextra" "-Werror")
install(TARGETS unisparks-test DESTINATION bin COMPONENT "tests")

# BENCH
add_executable(unisparks-bench ${BENCH_SOURCES})
target_link_libraries(unisparks-bench unisparks)
set_target_properties(unisparks-bench PROPERTIES COMPILE_OPTIONS "-std=c++11;-fPIC;-Wall;-Wextra;-Werror;-o2")
install(TARGETS unisparks-bench DESTINATION bin COMPONENT "bench")

