cmake_minimum_required(VERSION 2.8.3)
project(talker_listener)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
  std_srvs
)

add_message_files(
   FILES
   Data.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS roscpp message_runtime
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(talker_node src/talker.cpp)
target_link_libraries(talker_node ${catkin_LIBRARIES})

add_executable(listener_node src/listener.cpp)
target_link_libraries(listener_node ${catkin_LIBRARIES})

add_executable(client_node src/client.cpp)
target_link_libraries(client_node ${catkin_LIBRARIES})