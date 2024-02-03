cmake_minimum_required(VERSION 3.8)
project(distance_control)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  find_package(ament_cmake_gtest REQUIRED)

  set(TESTFILES
      test/main.cpp
      test/distance_control_node_test.cpp
      )
  # Add a gtest executables
  ament_add_gtest(${PROJECT_NAME}_test ${TESTFILES})
  target_link_libraries(${PROJECT_NAME}_test distance_control_lib)

  install(TARGETS
        ${PROJECT_NAME}_test
        # Install the generated test executable file to the path after DESTINATION
        DESTINATION lib/${PROJECT_NAME})
  # uncomment to enforce lintners and static code analyzers defined in ament_lint_common package        
  # ament_lint_auto_find_test_dependencies()
endif()

## ADD LIBRARY
include_directories(include)
add_library(distance_control_lib src/distance_control.cpp include/distance_control/distance_control_header.h)
ament_target_dependencies(distance_control_lib 
  rclcpp
  std_msgs)

ament_export_targets(distance_control_lib HAS_LIBRARY_TARGET)

install(
  DIRECTORY include/distance_control
  DESTINATION include
)

## ADD EXECUTABLE
add_executable(main src/main.cpp)
target_link_libraries(main PUBLIC distance_control_lib)

install(TARGETS distance_control_lib
  DESTINATION lib/distance_control_lib)

install(TARGETS 
  main
  DESTINATION lib/${PROJECT_NAME}/
)

install(
  TARGETS distance_control_lib
  EXPORT distance_control_lib
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

ament_package()