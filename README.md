# mini-dnn
a vs2017 C++ demo of deep neural networks. It is implemented purely in C++, only depends on Eigen lib.
## How to build
## Win10 (Visual Studio2017)
A Visual Studio solution `mini-dnn.sln` has been generated. Open the solution file and build all projects, the static lib and examples have been built.
We can ref the [blog](https://blog.csdn.net/qq_44894692/article/details/105163208?utm_medium=distribute.pc_relevant.none-task-blog-baidujs_title-0&spm=1001.2101.3001.4242) which introduces the configuration of Eigen under VS2017

Download and unzip [mnist](https://pan.baidu.com/s/1LjNPLkB5nvYufbpraFH33g) dataset by the baiduyun code `45x2` in `mini-dnn/mini-dnn`
Run `demo.cpp`
## Result
simple neural network with 3 FC layers can obtain 0.97+ accuracy on MNIST testset.  you can select layers by yourself.

## Acknowledge
Thanks for the [repo](https://github.com/iamhankai/mini-dnn-cpp)