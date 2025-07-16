cmake_minimum_required(VERSION 3.22)
project(EmsTest)

set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

if(EMSCRIPTEN)
  set(EXE_NAME index)
  set(GLSL_VERSION "300 es")

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/html/index.html
    ${CMAKE_CURRENT_BINARY_DIR}
  )

  find_package(OpenGL REQUIRED)
else()
  set(EXE_NAME ${CMAKE_PROJECT_NAME})
  set(GLSL_VERSION "330 core")

  if(SYS_GL_HEADERS)
    find_package(OpenGL REQUIRED)
  else()
    add_subdirectory(deps/glad/)
  endif()

  add_subdirectory(deps/glfw/)
endif()

add_subdirectory(deps/slim/)

set(SOURCES
  src/main.cpp
  src/camera.cpp
  src/shader_program.cpp
  src/util/file_handling.cpp
  src/window.cpp
)

set(RESOURCES
  res/shaders/square.vert
  res/shaders/square.frag
)

set(abs_paths "")

foreach(file_path ${RESOURCES})
  if(file_path MATCHES ".+\.vert$" OR file_path MATCHES ".+\.frag$")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${file_path}
      ${CMAKE_CURRENT_BINARY_DIR}/${file_path}
    )
  else()
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${file_path}
      ${CMAKE_CURRENT_BINARY_DIR}/${file_path} COPYONLY
    )
  endif()

  list(APPEND abs_paths ${CMAKE_CURRENT_BINARY_DIR}/${file_path})
endforeach()

add_executable(${EXE_NAME} ${SOURCES})

target_compile_options(${EXE_NAME} PRIVATE
  $<$<COMPILE_LANG_AND_ID:C,Clang>:-std=c99;-Wall;-pedantic-errors>
  $<$<COMPILE_LANG_AND_ID:CXX,Clang>:-std=c++17;-Wall;-pedantic-errors>
)

target_compile_definitions(${EXE_NAME}
  PRIVATE GLFW_INCLUDE_NONE
  PRIVATE GL_GLEXT_PROTOTYPES
)

if(EMSCRIPTEN)
  execute_process(COMMAND emcc --cflags
    OUTPUT_VARIABLE EM_CFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  set(EM_LFLAGS "--embed-file res/ -sUSE_GLFW=3 "
                "-sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2"
  )

  string(REPLACE ";" "" EM_LFLAGS "${EM_LFLAGS}")

  set_target_properties(${EXE_NAME} PROPERTIES
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
    COMPILE_FLAGS ${EM_CFLAGS}
    LINK_FLAGS ${EM_LFLAGS}
    LINK_DEPENDS "${abs_paths}"
  )

  target_compile_definitions(${EXE_NAME}
    PRIVATE SYS_GL_HEADERS
    PRIVATE EMSCRIPTEN
  )
else()
  set_target_properties(${EXE_NAME} PROPERTIES
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
  )

  if(SYS_GL_HEADERS)
    target_compile_definitions(${EXE_NAME} PRIVATE SYS_GL_HEADERS)
    target_link_libraries(${EXE_NAME} PRIVATE OpenGL::GL)
  else()
    target_link_libraries(${EXE_NAME} PRIVATE glad)
  endif()

  target_link_libraries(${EXE_NAME} PRIVATE glfw)
endif()

target_link_libraries(${EXE_NAME} PRIVATE slim)
