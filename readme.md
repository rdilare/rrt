## Assignment status
1. Implemented RRT and RRT* algorithm in python.
2. Implemented RRT in C++.
   1. The code is not implemented properly.
   2. It often shows Segmentation fault (core dumped) error.
   3. Although sometimes it works fine. (I couldn't figure out the problem yet.)
3. visualization is also available in python.


## variables defination
- `xlim` = (x_min, x_max); x-axis limit for space.
- `ylim` = (y_min, y_max); y-axis limit for space.
- `goal_threshold` = threshold for reaching goal.
- `loop_count` = max. no. of loop iterations.
- `max_segment_length` = max. distance for new_node from tree.



## How to run.


### PYTHON
got to python folder and activate the virtual environment and install the dependencies. (I have used python3.8)
```shell
cd python
pip install -r requirements.txt
```
folder description:
- `main_rrt.py` : RRT implementation
- `main_rrt*.py` : RRT* implementation
- `data.py` : output will be saved in this file for visualization
- `visualization.py` : code for visualization
  
use the following command to run RRT.
```shell
python main_rrt.py
```

use the following command to run RRT*.
```shell
python main_rrt*.py
```
run the following command for visualizing the solution.
```shell
python visualization.py
```

### C++

go to c++ folder and compile the code. (compiled a.out file should already be there).
```shell
g++ rrt.cpp
```

*there is no compilation error in my system. the code may have memory issue so it may not work propery.*


after compilation run the binary file
```shell
./a.out
```