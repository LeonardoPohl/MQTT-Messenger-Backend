cmake_minimum_required(VERSION 3.15...4.0)

set(CMAKE_CXX_STANDARD 20)

project(MqttBackend)

# Enable FetchContent
include(FetchContent)

# Paho MQTT C requires the C library, so fetch it as well
FetchContent_Declare(
    paho-mqtt-c
    GIT_REPOSITORY https://github.com/eclipse/paho.mqtt.c.git
    GIT_TAG        v1.3.14
)

# Set install location for the C lib
set(PAHO_MQTT_C_INSTALL_DIR ${CMAKE_BINARY_DIR}/paho-mqtt-c-install)

# Configure paho.mqtt.c build options before it's fetched
set(PAHO_BUILD_STATIC TRUE CACHE BOOL "Build static lib" FORCE)
set(PAHO_BUILD_SHARED FALSE CACHE BOOL "Don't build shared lib" FORCE)
set(PAHO_WITH_SSL FALSE CACHE BOOL "Disable SSL" FORCE)
set(PAHO_BUILD_DOCUMENTATION FALSE CACHE BOOL "No docs" FORCE)
set(PAHO_ENABLE_TESTING FALSE CACHE BOOL "No tests" FORCE)
set(CMAKE_INSTALL_PREFIX ${PAHO_MQTT_C_INSTALL_DIR} CACHE PATH "Install path" FORCE)

FetchContent_MakeAvailable(paho-mqtt-c)

# Force installation of paho.mqtt.c
install(TARGETS paho-mqtt3a DESTINATION lib)
install(DIRECTORY ${paho-mqtt-c_SOURCE_DIR}/src/ DESTINATION include FILES_MATCHING PATTERN "*.h")

# Fetch Paho MQTT C++
FetchContent_Declare(
    paho-mqtt-cpp
    GIT_REPOSITORY https://github.com/eclipse/paho.mqtt.cpp.git
    GIT_TAG        v1.5.3
)

# Tell it where to find the installed paho.mqtt.c
set(eclipse-paho-mqtt-c_DIR "${PAHO_MQTT_C_INSTALL_DIR}/lib/cmake/eclipse-paho-mqtt-c" CACHE PATH "" FORCE)

FetchContent_MakeAvailable(paho-mqtt-cpp)


# Your source and header files
file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.h)

# Create executable
add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

# Include your headers
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link Paho MQTT C++ (it automatically links to the C lib)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    paho-mqttpp3
    paho-mqtt3a  # Static C library (or paho-mqtt3c if built shared)
)

