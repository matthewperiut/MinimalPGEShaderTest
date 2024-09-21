cmake_minimum_required(VERSION 3.29)
set(PROJECT_NAME shader)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

file (GLOB MY_SRC
        "src/*"
        "src/imgui/*")

if (WIN32 OR LINUX)
    add_executable(${PROJECT_NAME} ${MY_SRC})
    file(COPY src/assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)
endif (WIN32 OR LINUX)

find_package(GLEW REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)

find_package(PNG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE PNG::PNG)

if(${CMAKE_SYSTEM} MATCHES "Linux")
    set(LINUX 1)
endif(${CMAKE_SYSTEM} MATCHES "Linux")

if (UNIX)
    # X11
    if(LINUX)
        find_package(X11 REQUIRED)
        include_directories(${X11_INCLUDE_DIR})
        link_directories(${X11_LIBRARIES})
        target_link_libraries(${PROJECT_NAME} PRIVATE ${X11_LIBRARIES})
    endif(LINUX)
    # GLUT
    if(APPLE)
        find_package(GLUT REQUIRED)
        include_directories(${GLUT_INCLUDE_DIR})
        link_directories(${GLUT_LIBRARIES})
        target_link_libraries(${PROJECT_NAME} PRIVATE ${GLUT_LIBRARIES})
    endif(APPLE)

    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})
    link_directories(${OPENGL_LIBRARIES})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})

    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
endif (UNIX)