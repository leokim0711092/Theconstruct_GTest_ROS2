#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include "gtest/gtest.h"
#include <memory>

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

    node = rclcpp::Node::make_shared("test_publisher");

    data_publisher_ =
        node->create_publisher<std_msgs::msg::Float32>("data_topic", 10);

    data_subscriber_ = node->create_subscription<std_msgs::msg::Float32>(
        "data_topic", 10,
        std::bind(&PubSubscriberTestFixture::received_data_callback, this, _1));
  }

  double publisherSubscriberTest(float test_data);

protected:
  std::shared_ptr<rclcpp::Node> node;

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
    rclcpp::spin_some(node);
  }
  return received_data_;
}

TEST_F(PubSubscriberTestFixture, SimpleTest30) {
  EXPECT_DOUBLE_EQ(30.0, publisherSubscriberTest(30.0));
}