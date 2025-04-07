cmake_minimum_required(VERSION 3.10)

project(ur10_mj_description VERSION 1.0.0)
set(ROBOT_NAME "ur10")

if(NOT TARGET mc_mujoco)
  find_package(mc_mujoco REQUIRED)
endif()

option(SRC_MODE "Use files in the repository instead of installed files" OFF)

# Specify variant models
set(ur_models
    ur10
)

foreach(MODEL IN LISTS ur_models)
    if(SRC_MODE)
        set(ROBOT_XML_MODEL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/xml/${MODEL}.xml")
        set(ROBOT_PDGAINS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/pdgains/${MODEL}/PDgains_sim.dat")
    else()
        set(ROBOT_XML_MODEL_PATH "${MC_MUJOCO_SHARE_DESTINATION}/${ROBOT_NAME}/xml/${MODEL}.xml")
        set(ROBOT_PDGAINS_PATH "${MC_MUJOCO_SHARE_DESTINATION}/${ROBOT_NAME}/pdgains/${MODEL}/PDgains_sim.dat")
    endif()

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/mc_mujoco/ur10.in.yaml "${CMAKE_CURRENT_BINARY_DIR}/mc_mujoco/${MODEL}.yaml")
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/mc_mujoco/${MODEL}.yaml" DESTINATION "${MC_MUJOCO_SHARE_DESTINATION}")
    install(DIRECTORY pdgains DESTINATION "${MC_MUJOCO_SHARE_DESTINATION}/${ROBOT_NAME}")

endforeach()

install(DIRECTORY meshes DESTINATION "${MC_MUJOCO_SHARE_DESTINATION}/${ROBOT_NAME}")
install(DIRECTORY xml DESTINATION "${MC_MUJOCO_SHARE_DESTINATION}/${ROBOT_NAME}" FILES_MATCHING PATTERN "*.xml")