cmake_minimum_required(VERSION 3.15)
project(MqttMessenger)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Define the installation path for Paho MQTT C and C++ libraries
set(PAHO_MQTT_INSTALL_DIR "/app/paho_mqtt_cpp/build")

# Include directories for both Paho MQTT C and C++ libraries
include_directories(
    ${PAHO_MQTT_INSTALL_DIR}/include
    /app/paho.mqtt.cpp/include
)

# Add your source files (replace with your actual source files)
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Create your executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link against the installed Paho MQTT C and C++ static libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${PAHO_MQTT_INSTALL_DIR}/lib/libpaho-mqtt3a.a      # Link against the C library
    /app/paho.mqtt.cpp/build/libpaho-mqttpp3.a          # Link against the C++ library
)
