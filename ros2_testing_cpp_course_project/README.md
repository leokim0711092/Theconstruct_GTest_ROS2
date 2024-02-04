# Credits

Source:  https://github.com/samialperen/ros2_move_robot.git

# Step 1

`colcon build --packages-select ros2_draw_squares ros2_draw_squares_custom_msgs`  

# 2. Run map to odom static transform listener

`ros2 run tf2_ros static_transform_publisher 0 0 0 0 0 0 map odom`  

# 3. Run the service server node with

`ros2 launch ros2_draw_squares move_robot_in_square_service_server.launch.py`  

# 4. Run the service client node with

`ros2 launch ros2_draw_squares call_move_robot_in_square_service_server.launch.py`  


---


`ros2 run ros2_draw_squares move_robot_node`  