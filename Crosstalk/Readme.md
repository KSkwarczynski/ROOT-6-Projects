Program to study crosstalk in Super FGD prototype.

## How to run
download repository from https://github.com/MrMefodij/SFGD_Unpack_august <br/>
next add CrosstalkStudy.cpp to **examples** <br/>
replace **CMakeLists.txt** in examples with one in this repository. <br/>

```
$ cd build <br/>
$ cmake ../ <br/>
$ make <br/>
```

## Programs description
PlotMaker.cpp makes nice histograms from created ROOT files. <br/>
DataMerger.cpp combine a few data sets into one to increase statistic. <br/>
GraphMaker.cpp creates graphs.
