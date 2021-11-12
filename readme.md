## Assignment status
1. Implemented RRT and RRT* algorithm in python.
2. Implemented RRT and RRT* in C++.
3. visualization of nodes, tree, path, obstacles is also available.


## variables defination
- `xlim` = (x_min, x_max); x-axis limit for space.
- `ylim` = (y_min, y_max); y-axis limit for space.
- `goal_threshold` = threshold for reaching goal.
- `loop_count` = max. no. of loop iterations.
- `max_segment_length` = max. distance for new_node from tree.
- `neighborhood_radius` = for rrt* algorithm.



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

## Visualization

- nodes, tree, path, obstacles can be visualized
- after running the algorithm (in python or C++) got to rrt folder and run the python code for visualization.

```shell
cd rrt
python visualization.py
```