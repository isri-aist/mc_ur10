# Here we find a typical ROS description package, this set the MC_UR5E_DESCRIPTION_PATH CMake variable
find_description_package(mc_ur10_description)
if(EXISTS "${MC_UR10_DESCRIPTION_PATH}/share/mc_ur10_description")
  set(MC_UR10_DESCRIPTION_PATH "${MC_UR10_DESCRIPTION_PATH}/share/mc_ur10_description")
endif()

# Generate the robot module C++ code using this value
configure_file(ur10.in.cpp "${CMAKE_CURRENT_BINARY_DIR}/ur10.cpp")

set(ur10_SRC
  "${CMAKE_CURRENT_BINARY_DIR}/ur10.cpp"
)
set(ur10_HDR
  ur10.h
)

add_robot(ur10 ${ur10_SRC} ${ur10_HDR})
target_include_directories(ur10 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
