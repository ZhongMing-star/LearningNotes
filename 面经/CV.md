# 目标检测

目标检测的发展脉络可以划分为两个周期：传统目标检测算法时期(1998年-2014年)和基于深度学习的目标检测算法时期(2014年-至今)。而基于深度学习的目标检测算法又发展成了两条技术路线：**Anchor based**方法(一阶段，二阶段)和**Anchor free**方法。下图2-1展示了从2001年至2021年目标检测领域中，目标检测发展路线图。

![img](image\v2-e0a477f5a1fb362f72123676ef403894_1440w-16970923169758.webp)

## **2.1 传统目标检测算法**

不同于现在的卷积神经网络可以自动提取高效特征进行图像表示，以往的传统目标检测算法主要基于手工提取特征。传统检测算法流程可概括如下：

1. 选取感兴趣区域，选取可能包含物体的区域
2. 对可能包含物体的区域进行特征提取
3. 对提取的特征进行检测分类

## 2.2 深度学习的目标检测方法

### **2.2.1 Anchor-Based中的Two-stage目标检测算法**

基于手工提取特征的传统目标检测算法进展缓慢，性能低下。直到2012年卷积神经网络(Convolutional Neural Networks, CNNs)的兴起将目标检测领域推向了新的台阶。基于CNNs的目标检测算法主要有两条技术发展路线：**anchor-based和anchor-free方法**，**而anchor-based方法则包括一阶段和二阶段检测算法(二阶段目标检测算法一般比一阶段精度要高，但一阶段检测算法速度会更快)。**

二阶段检测算法主要分为以下两个阶段
**Stage1**：从图像中生成region proposals
**Stage2**：从region proposals生成最终的物体边框。

#### RCNN

![img](image\v2-554d6976d29262731db56def37366589_1440w.webp)

#### SPPNet

![img](image\v2-43a86774acdaecc0209c8a049601c251_1440w.webp)

#### Fast RCNN

![img](image\v2-04eeba8b7e3aee73b29687c6d3798a0b_1440w.webp)

#### **Faster RCNN**

![img](image\v2-5816b6fff1242fb25011a83eb249972a_1440w.webp)

#### FPN



![img](image\v2-15dd683195074035119181da76d458f1_1440w.webp)

#### **Cascade RCNN**

![img](image\v2-a9c78d59a62d2be6a733657ed0d73695_1440w.webp)

 Faster RCNN完成了对目标候选框的两次预测，其中RPN一次，后面的检测器一次，而**Cascade RCNN[9]**则更进一步将后面检测器部分堆叠了几个级联模块，并采用不同的IOU阈值训练，这种级联版的Faster RCNN就是Cascade RCNN。通过提升IoU阈值训练级联检测器，可以使得检测器的定位精度更高，在更为严格的IoU阈值评估下，Cascade R-CNN带来的性能提升更为明显。Cascade RCNN将二阶段目标检测算法的精度提升到了新的高度。

### **2.2.2 Anchor-based中的one-stage目标检测算法**

一阶段目标检测算法不需要region proposal阶段，直接产生物体的类别概率和位置坐标值，经过一个阶段即可直接得到最终的检测结果，因此有着更快的检测速度。

#### Yolov1 

![img](image\v2-6234a24c80035bea49e536bf50644630_1440w.webp)

 **YOLO v1[10]**是第一个一阶段的深度学习检测算法，其检测速度非常快，该算法的思想就是将图像划分成多个网格，然后为每一个网格同时预测边界框并给出相应概率。例如某个待检测目标的中心落在图像中所划分的一个单元格内，那么该单元格负责预测该目标位置和类别。

#### **SSD**

![img](image\v2-1f6e06739e08384e4acc877bd1665040_1440w.webp)

 **SSD[11]**算法的主要创新点是提出了Multi-reference和Multi-resolution的检测技术。SSD算法和先前的一些检测算法的区别在于：先前的一些检测算法只是在网络最深层的分支进行检测，而SSD有多个不同的检测分支，不同的检测分支可以检测多个尺度的目标，所以SSD在多尺度目标检测的精度上有了很大的提高，对小目标检测效果要好很多。

#### **YOLO v2**

![img](image\v2-536e887aefb48dbbeb32f7e99ff12a6e_1440w.webp)

相比于YOLO v1，**YOLO v2[12]**在精度、速度和分类数量上都有了很大的改进。在速度上(Faster)，YOLO v2使用DarkNet19作为特征提取网络，该网络比YOLO v2所使用的VGG-16要更快。在分类上(Stronger)，YOLO v2使用目标分类和检测的联合训练技巧，结合Word Tree等方法，使得YOLO v2的检测种类扩充到了上千种。下图2-2展示了YOLO v2相比于YOLO v1在提高检测精度(Better)上的改进策略。

![img](image\v2-a965d281190f92ea1242ee7eff90b459_1440w.webp)

#### **RetinaNet**

![img](image\v2-160eec0c3c60c8e17bf03a84b10a557e_1440w.webp)

 尽管一阶段检测算推理速度快，但精度上与二阶段检测算法相比还是不足。**RetinaNet[13]**论文分析了一阶段网络训练存在的类别不平衡问题，提出能根据Loss大小自动调节权重的Focal loss，代替了标准的交叉熵损失函数，使得模型的训练更专注于困难样本。同时，基于FPN设计了RetinaNet，在精度和速度上都有不俗的表现。

#### **YOLO v3**

![img](D:\vscode\LeetCode\Node\image\v2-683ec8db9aaf467e8adc011e6da59d8e_1440w.webp)

####  **YOLO v4**

![img](D:\vscode\LeetCode\Node\image\v2-c36a3262c0582a7805b1e448ba15f711_1440w.webp)

####  **YOLO v5**

![img](D:\vscode\LeetCode\Node\image\v2-69b21f7d6785ea465a0fed29adc91eb7_1440w.webp)

#### YOLO v7

![img](D:\vscode\LeetCode\Node\image\v2-8d1b3e67a9895dfb381f5756643dfe91_1440w.webp)

#### YOLO v8

![img](image\v2-bce8ec9e7b5f8f6781c8cf6ed45f89c0_1440w.webp)

### **2.2.3 Anchor-based目标检测算法局限性**

基于Anchor的目标检测算法主要有以下四大缺点：

1. Anchor的大小，数量，长宽比对于检测性能的影响很大(通过改变这些超参数Retinanet在COCO benchmark上面提升了4%的AP)，因此Anchor based的检测性能对于anchor的大小、数量和长宽比都非常敏感。
2. 这些固定的Anchor极大地损害了检测器的普适性，导致对于不同任务，其Anchor都必须重新设置大小和长宽比。
3. 为了去匹配真实框，需要生成大量的Anchor，但是大部分的Anchor在训练时标记为负样本，所以就造成了样本极度不均衡问题(没有充分利用fore-ground)。
4. 在训练中，网络需要计算所有Anchor与真实框的IOU，这样就会消耗大量内存和时间。

### **2.4 Anchor-Free中的目标检测算法**

