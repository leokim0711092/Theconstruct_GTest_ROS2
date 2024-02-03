#include "distance_control/distance_control_header.h"
#include <rclcpp/rclcpp.hpp>

int main(int argc, char *argv[]) {

  rclcpp::init(argc, argv);

  auto node = std::make_shared<DistanceControl>("distance_to_vehicle_ahead", "throttle", "distance_control");

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}