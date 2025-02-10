#include "ur10.h"

#include <RBDyn/parsers/urdf.h>

#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;

namespace
{

// This is set by CMake, see CMakeLists.txt
static const std::string MC_UR10_DESCRIPTION_PATH = "@MC_UR10_DESCRIPTION_PATH@";

} // namespace

namespace mc_robots
{

UR10RobotModule::UR10RobotModule() : mc_rbdyn::RobotModule(MC_UR10_DESCRIPTION_PATH, "ur10")
{
  // True if the robot has a fixed base, false otherwise
  bool fixed = true;
  // Makes all the basic initialization that can be done from an URDF file
  init(rbd::parsers::from_urdf_file(urdf_path, fixed));

  // Automatically load the convex hulls associated to each body
  std::string convexPath = path + "/convex/" + name + "/";
  bfs::path p(convexPath);
  if(bfs::exists(p) && bfs::is_directory(p))
  {
    std::vector<bfs::path> files;
    std::copy(bfs::directory_iterator(p), bfs::directory_iterator(), std::back_inserter(files));
    for(const bfs::path & file : files)
    {
      size_t off = file.filename().string().rfind("-ch.txt");
      if(off != std::string::npos)
      {
        std::string name = file.filename().string();
        name.replace(off, 7, "");
        if(name == "upperarm")
        {
          _convexHull["upper_arm_link"] = std::pair<std::string, std::string>("upper_arm_link", file.string());
        }
        else if(name == "wrist1")
        {
          _convexHull["wrist_1_link"] = std::pair<std::string, std::string>("wrist_1_link", file.string());
        }
        else if(name == "wrist2")
        {
          _convexHull["wrist_2_link"] = std::pair<std::string, std::string>("wrist_2_link", file.string());
        }
        else if(name == "wrist3")
        {
          _convexHull["wrist_3_link"] = std::pair<std::string, std::string>("wrist_3_link", file.string());
        }
        else
        {
          _convexHull[name + "_link"] = std::pair<std::string, std::string>(name + "_link", file.string());
        }
      }
    }
  }

  // Define a minimal set of self-collisions
  _minimalSelfCollisions = {
      {"base_link", "upper_arm_link", 0.01, 0.001, 0.0},
      {"base_link", "forearm_link", 0.01, 0.001, 0.0},
      {"base_link", "wrist_1_link", 0.01, 0.001, 0.0},
      {"base_link", "wrist_2_link", 0.01, 0.001, 0.0},
      {"base_link", "wrist_3_link", 0.01, 0.001, 0.0},

      {"shoulder_link", "forearm_link", 0.01, 0.001, 0.0},
      {"shoulder_link", "wrist_1_link", 0.01, 0.001, 0.0},
      {"shoulder_link", "wrist_2_link", 0.01, 0.001, 0.0},
      {"shoulder_link", "wrist_3_link", 0.01, 0.001, 0.0},

      {"upper_arm_link", "wrist_1_link", 0.01, 0.001, 0.0},
      {"upper_arm_link", "wrist_2_link", 0.01, 0.001, 0.0},
      {"upper_arm_link", "wrist_3_link", 0.01, 0.001, 0.0}};
  _commonSelfCollisions = _minimalSelfCollisions;

  //Ref joint order
  _ref_joint_order = {"shoulder_pan_joint", "shoulder_lift_joint", "elbow_joint",
		      "wrist_1_joint", "wrist_2_joint", "wrist_3_joint"
  };

  rsdf_dir = path + "/rsdf/" + name + "/";
  calib_dir = path + "/calib";

  _stance["shoulder_pan_joint"] = {mc_rtc::constants::toRad(0)};
  _stance["shoulder_lift_joint"] = {mc_rtc::constants::toRad(-140)};
  _stance["elbow_joint"] = {mc_rtc::constants::toRad(110)};
  _stance["wrist_1_joint"] = {mc_rtc::constants::toRad(-60)};
  _stance["wrist_2_joint"] = {mc_rtc::constants::toRad(-90)};
  _stance["wrist_3_joint"] = {mc_rtc::constants::toRad(0)};

}

} // namespace mc_robots
