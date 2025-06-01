#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mqtt/async_client.h>

const std::string SERVER_ADDRESS = "tcp://test.mosquitto.org:1883";
const std::string CLIENT_ID = "simple_mqtt_client_cpp";
const std::string TOPIC = "test/sample";

class callback : public virtual mqtt::callback {
public:
    void message_arrived(mqtt::const_message_ptr msg) override {
        std::cout << "Message arrived on topic '" << msg->get_topic() << "': " 
                  << msg->to_string() << std::endl;
    }
};

int main() {
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);
    callback cb;
    client.set_callback(cb);

    mqtt::connect_options connOpts;
    connOpts.set_clean_session(true);

    try {
        std::cout << "Connecting to MQTT broker..." << std::endl;
        client.connect(connOpts)->wait();

        std::cout << "Subscribing to topic '" << TOPIC << "'..." << std::endl;
        client.subscribe(TOPIC, 1)->wait();

        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::cout << "Publishing a message..." << std::endl;
        client.publish(TOPIC, "Hello MQTT from C++!", 1, false)->wait();

        std::cout << "Waiting for messages (5 seconds)..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));

        std::cout << "Disconnecting..." << std::endl;
        client.disconnect()->wait();
    } 
    catch (const mqtt::exception& e) {
        std::cerr << "MQTT Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Done." << std::endl;
    return 0;
}
