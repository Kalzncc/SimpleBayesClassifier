# 基于C++的朴素贝叶斯分类器

## <a href="https://github.com/Kalzncc/MachineLearningImpl"> 主仓库 </a>

使用c++编写的朴素贝叶斯分类器，其中似然中的离散分量，以及先验概率使用拉普拉斯平滑，连续分量为正态分布。

**警告，此代码仅为初学学习之用，请勿用作任何工程项目！**
## 一、跑起来
### 方式一
使用vscode+cmake插件或者Clion打开目录。然后直接编译运行。
### 方式二
1、确保安装cmake环境，没有请先装cmake。
2、在工程目录下键入：

```sh
mkdir build
cd build
cmake ..
make
```
3、运行build目录下的程序Bayers_classifier程序

## 二、用起来
1、建立模型
```cpp
Simple_Bayes_Classifier::Info info;
/**
    struct Info {
        int sample_num; // 样例数量
        std::vector<int> header; // 样例格式，
                                 // 如当前分量为离散值则为样例可能取值的数量，
                                 // 如为连续值则填0，
                                 // 例如，现有样例格式为这样 :
                                 //           x0 属于 {"东","南","西","北"}
                                 //           x1 属于 {"左","右"}
                                 //           x2 属于 {x|0<x<100} 为连续值
                                 // 则 header={4, 2, 0}
                                                           
        int class_num; // 分类数量
        int sample_size; // 样例分量维度大小
    } 
 */
Simple_Bayes_Classifier model(info);
```
2、读取文件，训练模型
```cpp
model.train("data/1.txt"); // 文件格式为：每行一个样例，每个样例n个分量用空格隔开，最后为该样例所属分类
```
示例文件格式：

3、开始分类, 构造出一个待分类的样例，然后分类结果赋值到样例的belong_to字段
```cpp
Sample s;
s.add_parameter(x); s.add_parameter(y);
model.classify(s);
std::cout << s.belong_to << std::endl;
```
## 三、学起来

贝叶斯分类器的基石为Bayes公式：

$$P(A_i|B)=\frac{P(B|A_i)P(A_i)}{\sum_{j=1}^nP(B|A_j)P(A_j)}$$

若现在存在样例的向量为$\boldsymbol{x}$，而其所属分类为$c$的概率为：

$$P(c|\boldsymbol{x})=\frac{p(c)p(\boldsymbol{x}|c)}{p(\boldsymbol{x})}$$

其中，我们把$p(c)$称为先验概率（prior），而$p(\boldsymbol{x}|c)$则为似然（likelihood）而$p(\boldsymbol{x})$称为证据（evidence）。当分类器工作时，遵循$h(\boldsymbol{x})$，我们需要比较$n$种分类，选择概率最大的分类。
$$h(\boldsymbol{x})=argmax_{c\in Y}P(c|\boldsymbol{x})$$

而

$$P(c|\boldsymbol{x}) \propto p(c)p(\boldsymbol{x}|c)$$

所以我们可以忽略证据，针对每个待分类的样例，对每种分类计算先验概率和似然即可。

先验概率$p(c)$一般直接进行数量统计，即:
$$p(c)=\frac{|D_c|}{|D|}$$

其中$D_c$为训练集中。所属类别$c$的样例集，而$|D|$为全体训练集。

而计算较为困难的是似然$p(\boldsymbol{x}|c)$，在朴素贝叶斯中，我们认为向量$\boldsymbol{x}$的所有分量的取值是独立的,此时有:
$$p(\boldsymbol{x}|c)=\prod_{i=0}^np(x_i|c)$$

此时即可进行运算，这里如果$x_i$为离散值，则可以之前进行统计：

$$p(x_i|c)=\frac{|D_{i,c}|}{|D_c|}$$

其中$D_{i,c}$是训练集中满足，所属类别为$c$且$i$分量为$x_i$的集合。

而如果$x_i$为连续值，则这里可以讲其看成正态分布:

$$p(x_i|c)=\frac{1}{\sqrt{2\pi}\sigma_{i,c}}e^{-\frac{(x_i-\mu_{i,c} )^2}{2\sigma_{i,c}^2}}$$

其中$\sigma_{i,c}^2,\mu_{i,c}$分别为所属类别为$c$的训练集的$i$分量的方差和均值。

至此我们解决了朴素贝叶斯分类器。

在有些时候，向量$\boldsymbol{x}$的分量不是独立的，一种常见的情况是所有分量满足多维正态分布$N(\mu, \Sigma)$。为了清晰设置$exp(x)=e^x$

$$p(\boldsymbol{x})=\frac{1}{(2\pi)^{\frac{d}{2}}|\Sigma|^{\frac{1}{2}}}exp\left ( -\frac{1}{2} (\boldsymbol{x}-\boldsymbol{\mu} )^T\Sigma^{-1}(\boldsymbol{x}-\boldsymbol{\mu} ) \right ) $$

其中

$$\mu_i=E[x_i]$$
$$\Sigma_{i,j}=E[(x_i-\mu_i)(x_j-\mu_j)]$$

这里我们将结果取对数

$$g_i(\boldsymbol{x})=ln(p(\boldsymbol{x}|c_i)p(c_i))=lnp(\boldsymbol{x}|c_i)+lnp(c_i)$$

$$g_i(\boldsymbol{x})=-\frac{1}{2} (\boldsymbol{x}-\boldsymbol{\mu} )^T\Sigma^{-1}(\boldsymbol{x}-\boldsymbol{\mu} )-\frac{d}{2}ln2\pi -\frac{1}{2}ln|\Sigma_i|+lnp(c_i)$$

此时有决策函数：

$$g_{i,j}(x)=g_i(x)-g_j(x)$$

$g_{i,j}(x)=0$为决策界，当$g_{i,j}(x)\ge 0$归为$i$类，否则归为$j$。至此，我们讨论了贝叶斯分类器中，样例各分量满足多维正态分布的情况。

