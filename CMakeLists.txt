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

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/res/index.html
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

set(SRCS
  src/square.cpp
  src/ShaderProgram.cpp
)

set(SHADER_SRCS
  res/shaders/square.vert
  res/shaders/square.frag
)

add_executable(${EXE_NAME} ${SRCS})

set_directory_properties(PROPERTIES
  CMAKE_CONFIGURE_DEPENDS "${SHADER_SRCS}"
)

foreach(file_path ${SHADER_SRCS})
  string(REGEX MATCH "([^/]+)$" name "${file_path}")
  
  set(header_name ${name})
  string(APPEND header_name ".h")

  string(REGEX REPLACE "\\." "_" identifier "${name}")
  set(parsed_src "const char *${identifier} = \n")

  file(STRINGS ${file_path} lines)

  foreach(line ${lines})
    string(CONFIGURE "${line}" line)
    string(REGEX REPLACE "^(.+)$" "  \"\\1\\\\n\"\n" line "${line}")
    string(APPEND parsed_src "${line}")
  endforeach()

  string(REGEX REPLACE "\n$" ";\n" parsed_src "${parsed_src}")
  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/shaders/${header_name} "${parsed_src}")
endforeach()

target_include_directories(${EXE_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

if(EMSCRIPTEN)
  execute_process(COMMAND emcc --cflags
    OUTPUT_VARIABLE EM_CFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  set_target_properties(${EXE_NAME} PROPERTIES
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
    COMPILE_FLAGS ${EM_CFLAGS}
    LINK_FLAGS "-sUSE_GLFW=3 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2"
    # CMAKE_EXECUTABLE_SUFFIX ".html"
  )

  target_compile_definitions(${EXE_NAME}
    PRIVATE SYS_GL_HEADERS
    PRIVATE EMSCRIPTEN
  )
else()
  set_target_properties(${EXE_NAME} PROPERTIES
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
  )

  target_compile_options(${EXE_NAME} PRIVATE
    $<$<COMPILE_LANG_AND_ID:C,Clang>:-std=c99;-Wall>
    $<$<COMPILE_LANG_AND_ID:CXX,Clang>:-std=c++11;-Wall>
  )

  if(SYS_GL_HEADERS)
    target_compile_definitions(${EXE_NAME} PRIVATE SYS_GL_HEADERS)
    target_link_libraries(${EXE_NAME} PRIVATE OpenGL::GL)
  else()
    target_link_libraries(${EXE_NAME} PRIVATE glad)
  endif()

  target_link_libraries(${EXE_NAME} PRIVATE glfw)
endif()
