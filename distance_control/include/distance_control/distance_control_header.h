#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

class DistanceControl : public rclcpp::Node {
public:
  explicit DistanceControl(const std::string &sub_topic_name,
                           const std::string &pub_topic_name,
                           const std::string &node_name);

  double map_value(double x, double in_min, double in_max, double out_min,
                   double out_max);

private:
  std::unique_ptr<std_msgs::msg::Float32> output_msg_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr pub_;
  rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr sub_;
};