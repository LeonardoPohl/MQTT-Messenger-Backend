# Use the official Ubuntu base image
FROM ubuntu:22.04

# Install dependencies
RUN apt update && apt install -y \
    cmake \
    g++ \
    git \
    make \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /app

# Copy the project source code
RUN git submodule update --init --recursive

# Build libs

## paho-mqtt-cpp
WORKDIR /app/libraries/paho.mqtt.cpp
RUN git submodule init
RUN git submodule update

RUN cmake -Bbuild -H. -DPAHO_WITH_MQTT_C=ON -DPAHO_BUILD_EXAMPLES=ON
RUN cmake --build build/ --target install

# Create a build directory for your project
RUN mkdir /app/build
WORKDIR /app/build

RUN cmake ..
RUN make

# Specify the default command to run the app
CMD ["/app/build/MqttMessenger"]
