cmake_minimum_required(VERSION 3.15)
project(MqttMessenger)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Include directories for both Paho MQTT C and C++ libraries
include_directories(
    libraries/paho.mqtt.cpp/include
)

# Find the Paho MQTT C and C++ libraries
find_library(PAHO_MQTT_C_LIBRARY paho-mqtt3a HINTS libraries/paho.mqtt.cpp/build/externals/paho-mqtt-c/src)
find_library(PAHO_MQTT_CPP_LIBRARY paho-mqttpp3 HINTS libraries/paho.mqtt.cpp/build/src) 

# Add your source files (replace with your actual source files)
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Create your executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link against the installed Paho MQTT C and C++ libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${PAHO_MQTT_C_LIBRARY}
    ${PAHO_MQTT_CPP_LIBRARY}
)
