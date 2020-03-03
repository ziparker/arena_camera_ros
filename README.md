Arena Camera deriver for ROS


## Getting Started

### Prerequisites
* Ubuntu-16.04 xenial
* ROS kinetic
* ArenaSDK binraies

### Basic Setup
#### Environment for ArenaSDK 

```shell
echo "export ARENA_ROOT=<ArenaSDK binaries root folder>">> ~/.bashrc
echo "export ARENA_ROOT=<ArenaSDK binaries root folder>">> ~/.zshrc
source ~/.bashrc
source ~/.zshrc
```

#### Workspace
Copy the included image_encoding.h to your ROS include folder after 
backing up the old one (if existed). The custom image_encoding.h is
included to enable streaming support for LUCID’s Helios camera.
```shell
sudo cp -f \
    /opt/ros/kinetic/include/sensor_msgs/image_encodings.h \
    /opt/ros/kinetic/include/sensor_msgs/image_encodings.h.bak
sudo cp -f \
    <Repo root folder>/catkin_ws/inc/image_encodings.h \
    /opt/ros/kinetic/include/sensor_msgs/image_encodings.h
```
