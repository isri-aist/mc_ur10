option(INSTALL_MUJOCO_DESCRIPTION "Install mc_mujoco description" OFF)

if(${INSTALL_MUJOCO_DESCRIPTION})
    add_subdirectory(mujoco_description)
endif()