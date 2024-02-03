#include "distance_control/distance_control_header.h"

DistanceControl::DistanceControl(const std::string &sub_topic_name,
                                 const std::string &pub_topic_name,
                                 const std::string &node_name)
    : Node(node_name) {

  auto callback =
      [this](const std_msgs::msg::Float32::SharedPtr input_msg) -> void {
    RCLCPP_DEBUG(this->get_logger(), "I heard: [%f]", input_msg->data);

    double throttle = map_value(input_msg->data, 0, 50, -1.0, 1.0);

    output_msg_ = std::make_unique<std_msgs::msg::Float32>();
    output_msg_->data = throttle;
    RCLCPP_DEBUG(this->get_logger(), "Publishing: '%f'", output_msg_->data);
    pub_->publish(std::move(output_msg_));
  };

  sub_ =
      create_subscription<std_msgs::msg::Float32>(sub_topic_name, 10, callback);
  rclcpp::QoS qos(rclcpp::KeepLast(7));
  pub_ = this->create_publisher<std_msgs::msg::Float32>(pub_topic_name, qos);
}

double DistanceControl::map_value(double x, double in_min, double in_max,
                                  double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}