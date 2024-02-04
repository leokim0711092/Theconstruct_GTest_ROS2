#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include "gtest/gtest.h"
#include <memory>

#include "distance_control/distance_control_header.h"

using std::placeholders::_1;
using namespace std::chrono_literals;

class RclCppFixture {
public:
  RclCppFixture() { rclcpp::init(0, nullptr); }
  ~RclCppFixture() { rclcpp::shutdown(); }
};
RclCppFixture g_rclcppfixture;

class PubSubscriberTestFixture : public ::testing::Test {
public:
  PubSubscriberTestFixture() {
    callback_success_ = false;

    distCtrlNode = std::make_shared<DistanceControl>(
        "distance_to_vehicle_ahead", "throttle", "distance_control");

    pubSubNode = rclcpp::Node::make_shared("test_publisher");

    data_publisher_ = pubSubNode->create_publisher<std_msgs::msg::Float32>(
        "distance_to_vehicle_ahead", 10);

    data_subscriber_ = pubSubNode->create_subscription<std_msgs::msg::Float32>(
        "throttle", 10,
        std::bind(&PubSubscriberTestFixture::received_data_callback, this, _1));
  }

  double publisherSubscriberTest(float test_data);

protected:
  std::shared_ptr<rclcpp::Node> pubSubNode;
  std::shared_ptr<rclcpp::Node> distCtrlNode;

private:
  void received_data_callback(const std_msgs::msg::Float32::SharedPtr msg) {
    received_data_ = msg->data;
    callback_success_ = true;
  }

  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr data_publisher_;
  rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr data_subscriber_;

  double received_data_;
  bool callback_success_;
};

double PubSubscriberTestFixture::publisherSubscriberTest(float test_data) {
  std_msgs::msg::Float32 data_send;
  data_send.data = test_data;
  while (!callback_success_) {
    data_publisher_->publish(data_send);
    std::this_thread::sleep_for(1s);
    rclcpp::spin_some(pubSubNode);
    rclcpp::spin_some(distCtrlNode);
  }
  return received_data_;
}

TEST_F(PubSubscriberTestFixture, SimpleTest30) {
  EXPECT_FLOAT_EQ(0.2, publisherSubscriberTest(30.0));
}