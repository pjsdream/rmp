cmake_minimum_required(VERSION 3.1.0)
project(rmp)

# C++17
set(CMAKE_CXX_STANDARD 17)

# C++ thread
find_package(Threads)

# fPIC
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# eigen
find_package(Eigen3 REQUIRED)

# assimp
find_package(assimp REQUIRED)

# cppzmq
find_package(cppzmq REQUIRED)

# lodepng
set(LODEPNG_SOURCE_FILES lib/lodepng/lodepng.h lib/lodepng/lodepng.cpp)

# Qt5
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Find the Qt library
IF (APPLE)
  set(QT_PATH ~/Qt/5.9.2/clang_64)
  set(Qt5Widgets_DIR ${QT_PATH}/lib/cmake/Qt5Widgets)
  set(Qt5OpenGL_DIR ${QT_PATH}/lib/cmake/Qt5OpenGL)
ENDIF (APPLE)
IF (UNIX AND NOT APPLE)
  set(QT_PATH /playpen/jaesungp/Qt/5.9.2/gcc_64)
  set(Qt5Widgets_DIR ${QT_PATH}/lib/cmake/Qt5Widgets)
  set(Qt5OpenGL_DIR ${QT_PATH}/lib/cmake/Qt5OpenGL)
ENDIF (UNIX AND NOT APPLE)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(${Qt5OpenGL_DEFINITIONS})

include_directories(
  include
  lib
  ${EIGEN3_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
  ${Qt5OpenGL_INCLUDE_DIRS}
  ${ASSIMP_INCLUDE_DIRS}
  ${cppzmq_INCLUDE_DIR}
)

set(RMP_RENDERER_SOURCE_FILES
  # lodepng
  ${LODEPNG_SOURCE_FILES}

  include/rmp/renderer/shader/shader.h
  include/rmp/renderer/shader/light_shader.h
  include/rmp/renderer/camera/camera.h
  include/rmp/renderer/light/light.h
  include/rmp/renderer/material/material.h
  include/rmp/renderer/texture/texture.h
  include/rmp/renderer/texture/texture_loader.h
  include/rmp/renderer/mesh/mesh.h
  include/rmp/renderer/mesh/mesh_loader.h
  include/rmp/renderer/resource/resource_mesh.h
  include/rmp/renderer/resource/resource_texture.h
  include/rmp/renderer/gl_base.h
  include/rmp/renderer/renderer.h
  include/rmp/renderer/renderer_window.h
  include/rmp/renderer/renderer_ostream.h
  include/rmp/renderer/request/request.h
  include/rmp/renderer/request/request_mesh.h
  include/rmp/renderer/request/request_clear.h
  include/rmp/renderer/request/request_light.h
  include/rmp/renderer/request/request_frame_attach.h
  include/rmp/renderer/request/request_frame.h
  include/rmp/renderer/request/requests.h

  include/rmp/comm/context.h
  include/rmp/comm/subscriber.h
  include/rmp/comm/serializer.h
  include/rmp/comm/deserializer.h
  include/rmp/utils/timer.h

  src/renderer/shader/shader.cpp
  src/renderer/shader/light_shader.cpp
  src/renderer/camera/camera.cpp
  src/renderer/renderer_main.cpp
  src/renderer/renderer_window.cpp
  src/renderer/texture/texture_loader.cpp
  src/renderer/mesh/mesh_loader.cpp
  src/renderer/resource/resource_mesh.cpp
  src/renderer/resource/resource_texture.cpp)

add_executable(renderer ${RMP_RENDERER_SOURCE_FILES})
target_link_libraries(renderer
  Threads::Threads
  ${Qt5Widgets_LIBRARIES}
  ${Qt5OpenGL_LIBRARIES}
  ${ASSIMP_LIBRARIES}
  ${cppzmq_LIBRARY}
  stdc++fs
  )

add_executable(test_renderer
  include/rmp/renderer/renderer.h
  include/rmp/comm/publisher.h

  src/renderer/test_renderer.cpp
  )
target_link_libraries(test_renderer
  ${cppzmq_LIBRARY}
  )

add_executable(test_pub src/comm/test_pub.cpp)
target_link_libraries(test_pub ${cppzmq_LIBRARY})

add_executable(test_sub src/comm/test_sub.cpp)
target_link_libraries(test_sub ${cppzmq_LIBRARY})
