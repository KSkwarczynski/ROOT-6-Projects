Program to study crosstalk in Super FGD prototype.

How to run
download repository https://github.com/MrMefodij/SFGD_Unpack_august
next add CrosstalkStudy.cpp to examples
replace CMakeLists.txt in examples with this one.
go build
cmake ../
make


PlotMaker.cpp makes nice histograms from created ROOT files
DataMerger.cpp combine a few data sets into one to increase statistic
