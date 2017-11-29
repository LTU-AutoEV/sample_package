# Writing your own ROS packages and nodes

This guide will show you how to write your own ROS package and nodes using this package as a starting point.

## 1. Preliminaries

First, please make sure you have the `l2bot` and `l2bot_examples` packages installed.

  - [l2bot](https://github.com/LTU-AutoEV/l2bot)
  - [l2bot_examples](https://github.com/LTU-AutoEV/l2bot_examples)

## 2. Setting up your package

We will use this package as a starting point for creating your own package. Simply clone this repo into `~/l2bot_ws/src`:

```
~/l2bot_ws/src$ git clone https://github.com/LTU-AutoEV/sample_package.git
```

**Note**: Do not change the name of this package. It must be "sample_package" to work. A tutorial for changing the name of the package will be added later.

## 3. A tour of your new package

This package contains 2 files and 2 folders:

  - **CMakeLists.txt**: These are the instructions ROS uses to compile your programs when you run `catkin_make`. All new programs (nodes) must be listed in this file.
  - **package.xml**: This file contains information about the package like author and version number.
  - **launch/**: Folder containing launch files
    - **sample.launch**: A sample launch file that can be copy/pasted and changed to your liking.
  - **src/**: Folder containg all of your ROS programs
    - **my_node_sample.cpp**: A sample node that subscribes to the camera and publishes a Twist message to the l2bot.

## 4. Writing your first node

The files in this sample package are made to be duplicated and changed so we will use the existing cpp and launch files as a starting point. 

First decide what your program will be called. In this example, we will use the name **"line_follower"**.

Next, create a copy of `my_node_sample.cpp` named `line_follower.cpp` and a copy of `sample.launch` named `line_follower.launch`.

### a. CMakeLists.txt

Now we need to tell ROS abount our new program. Scroll down to the bottom of `CMakeLists.txt` and find the following lines:

```cmake
# Tell ROS that you have a cpp program you want it to compile
# Use the following format:
#    add_executable(FILENAME src/FILENAME.cpp)
add_executable(my_node_sample src/my_node_sample.cpp)

# Link ROS libs
# Use the following format:
#    target_link_libraries(FILENAME ${catkin_LIBRARIES})
target_link_libraries(my_node_sample ${catkin_LIBRARIES})
```

Copy and paste the `add_executable` and `target_link_libraries` commands and change `my_node_sample` to your node name `line_follower`. It should now read:

```cmake
# Tell ROS that you have a cpp program you want it to compile
# Use the following format:
#    add_executable(FILENAME src/FILENAME.cpp)
add_executable(my_node_sample src/my_node_sample.cpp)
add_executable(line_follower src/line_follower.cpp)

# Link ROS libs
# Use the following format:
#    target_link_libraries(FILENAME ${catkin_LIBRARIES})
target_link_libraries(my_node_sample ${catkin_LIBRARIES})
target_link_libraries(line_follower ${catkin_LIBRARIES})
```

### b. Your `launch` file

Scroll to the bottom of the launch file and look for the lines 

```xml
    <!-- ********** YOUR NODE GOES HERE ********* -->
    <!-- Change "my_node_sample" to the name of your node (usually the name of your cpp file) -->
    <node name="my_node_sample" pkg="sample_package" type="my_node_sample" output="screen" />
```

and change `my_node_sample` to the name of your node. **Do not copy and paste this line before changing, just change the existing line**.

Using our `line_follower` example the launch file would no read:

```xml
    <!-- ********** YOUR NODE GOES HERE ********* -->
    <!-- Change "my_node_sample" to the name of your node (usually the name of your cpp file) -->
    <node name="line_follower" pkg="sample_package" type="line_follower" output="screen" />
```

### c. Your cpp file

There is one more thing to do before writing any code. We must update our node with its new name.

Find the following line near the top of `src/line_follower.cpp`:

```c++
#define NODE_NAME "my_node_sample"
```

Change the name to match the name of your node.

```c++
#define NODE_NAME "line_follower"
```

### d. Writing your ROS node

You are now ready to write your own ROS node. Find the function `computeTwist` in `src/line_follower.cpp`. This function takes a `cv:Mat` (a video frame) and returns a `Twist`. This is the only function you need to change to make the l2bot drive based on camera input.

Try setting `speed` and `turn` to different values and running the program. The L2bot should follow the instructions.

For an example of using OpenCV see the following files from `l2bot_examples`:

  - [stop_on_white](https://github.com/LTU-AutoEV/l2bot_examples/blob/master/src/stop_on_white.cpp)
  - [cam_edge_detect](https://github.com/LTU-AutoEV/l2bot_examples/blob/master/src/cam_edge_detect.cpp)
