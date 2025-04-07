# UR10 robot module for [mc_rtc](https://jrl-umi3218.github.io/mc_rtc/)

This package contains a software representation, or a robot module, of [UR10](https://www.universal-robots.com/products/ur10-robot/) robot platform. This robot module is used by [mc_rtc](https://jrl-umi3218.github.io/mc_rtc/) framework to realize control of UR10 robot in simulation or in experiments with real platform.

## Required dependencies
- [mc_rtc](https://jrl-umi3218.github.io/mc_rtc/)
- [mc_ur10_description](https://github.com/isri-aist/mc_ur10_description)

## Build instructions

```bash
$ git clone https://github.com/isri-aist/mc_ur10
$ cd mc_ur10
$ mkdir build
$ cd build
$ cmake .. # -DINSTALL_MUJOCO_DESCRIPTION=ON 
$ make
$ sudo make install
```

- Using mc_rtc_superbuild 

Create a folder ur10 in `mc_rtc_superbuild/extensions` and create a `CMakeLists.txt` with the following content : 

```cmake
CreateCatkinWorkspace(ID ur_ws DIR "ur_ws" CATKIN_MAKE)

AptInstall(ros-$ENV{ROS_DISTRO}-ur-description)

AddCatkinProject(mc_ur10_description WORKSPACE ur_ws
  GITHUB isri-aist/mc_ur10_description
)


AddProject(mc_ur10
  GITHUB isri-aist/mc_ur10
  DEPENDS mc_ur10_description
  CMAKE_ARGS -DINSTALL_MUJOCO_DESCRIPTION=OFF 
)
```

If you want to install mujoco description set **`-DINSTALL_MUJOCO_DESCRIPTION=ON`**

## Basic run 

In `~/.config/mc_rtc/mc_rtc.yaml` : 

```
# General mc_rtc configuration to run a ur10 controller at 1kHz
MainRobot: UR10
Enabled: Posture
Timestep: 0.001
```

Then run the following commands in separate terminals : 

* ROS1

```bash
roscore 
roslaunch mc_rtc_ticker display.launch
mc_rtc_ticker 
```

> `roscore` is optional if you run `roslaunch mc_rtc_ticker display.launch` 

* ROS2

```bash
mc_rtc_ticker
ros2 launch mc_rtc_ticker display.launch
```

* Mujoco

```bash
mc_mujoco
```