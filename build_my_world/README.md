# robotic-software-engineer
Repository to projects developed in RSE program

##### Create Script
```sh
cd /Users/seponce/Desktop/gazebo/robotic-software-engineer/build_my_world
mkdir script
cd script
gedit hello.cpp
```

##### Sample Script
```c++
#include <gazebo/gazebo.hh>
namespace gazebo
{
  class WorldPluginMyRobot : public WorldPlugin
  {
    public: WorldPluginMyRobot() : WorldPlugin()
        {
            printf("Welcome to´s World!\n");
        }

    public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
        {
        }
  };
  GZ_REGISTER_WORLD_PLUGIN(WorldPluginMyRobot)
}
```

##### Create a CMakeLists.txt file
```sh
cd /Users/seponce/Desktop/gazebo/robotic-software-engineer/build_my_world
vi CMakeLists.txt
```

```text
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(hello SHARED script/hello.cpp)
target_link_libraries(hello ${GAZEBO_LIBRARIES})
```

##### Create a build directory and compile the code
```sh
cd /Users/seponce/Desktop/gazebo/project
mkdir build
cd build/
cmake ../
make # You might get errors if your system is not up to date!
export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:/Users/seponce/Desktop/gazebo/project/build
```

##### Open your world file and attach the plugin to it
```sh
cd /Users/seponce/Desktop/gazebo/project/world/
vi myworld.world
```

###### Copy this code
```xml
<plugin name="hello" filename="libhello.so"/>
```

###### and paste it under
```xml
<world name="default">
```

##### Launch the world file in Gazebo to load both the world and the plugin
```sh
cd /Users/seponce/Desktop/gazebo/project/world/
gazebo myworld.world
```

