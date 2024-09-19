

# 注意力机制

## Attention

### *Attention 的本质是什么*

Attention（注意力）机制如果浅层的理解，跟他的名字非常匹配。他的核心逻辑就是「**从关注全部到关注重点**」。

**将有限的注意力集中在重点信息上，从而节省资源，快速获得最有效的信息。**

**AI 领域的 Attention 机制**

Attention 机制最早是在计算机视觉里应用的，随后在 [NLP](https://link.zhihu.com/?target=https%3A//easyai.tech/ai-definition/nlp/) 领域也开始应用了，真正发扬光大是在 NLP 领域，因为 2018 年 [BERT](https://link.zhihu.com/?target=https%3A//easyai.tech/ai-definition/bert/) 和 GPT 的效果出奇的好，进而走红。而 [Transformer](https://link.zhihu.com/?target=https%3A//easyai.tech/ai-definition/transformer/) 和 Attention 这些核心开始被大家重点关注。

如果用图来表达 Attention 的位置大致是下面的样子：

![img](.\image\v2-add603bc247f87617e978c28b7bf1272_1440w.webp)

这里先让大家对 Attention 有一个宏观的概念，下文会对 Attention 机制做更详细的讲解。在这之前，我们先说说为什么要用 Attention。

## *Attention 的3大优点*

之所以要引入 Attention 机制，主要是3个原因：

1. **参数少：**模型复杂度跟 [CNN](https://link.zhihu.com/?target=https%3A//easyai.tech/ai-definition/cnn/)、[RNN](https://link.zhihu.com/?target=https%3A//easyai.tech/ai-definition/rnn/) 相比，复杂度更小，参数也更少。所以对算力的要求也就更小。
2. **速度快**：Attention 解决了 RNN 不能并行计算的问题。Attention机制每一步计算不依赖于上一步的计算结果，因此可以和CNN一样并行处理。
3. **效果好**： Attention 机制引入之前，有一个问题大家一直很苦恼：长距离的信息会被弱化，就好像记忆能力弱的人，记不住过去的事情是一样的。Attention 是挑重点，就算文本比较长，也能从中间抓住重点，不丢失重要的信息。下图红色的预期就是被挑出来的重点。

### Attention 的计算过程

第一步： query 和 key 进行相似度计算，得到权值

第二步：将权值进行归一化，得到直接可用的权重

第三步：将权重和 value 进行加权求和

>从上面的建模，我们可以大致感受到 Attention 的思路简单，**四个字“带权求和”就可以高度概括**，大道至简。做个不太恰当的类比，人类学习一门新语言基本经历四个阶段：死记硬背（通过阅读背诵学习语法练习语感）->提纲挈领（简单对话靠听懂句子中的关键词汇准确理解核心意思）->融会贯通（复杂对话懂得上下文指代、语言背后的联系，具备了举一反三的学习能力）->登峰造极（沉浸地大量练习）。
>这也如同attention的发展脉络，RNN 时代是死记硬背的时期，attention 的模型学会了提纲挈领，进化到 [transformer](https://link.zhihu.com/?target=https%3A//easyai.tech/ai-definition/transformer/)，融汇贯通，具备优秀的表达学习能力，再到 GPT、BERT，通过多任务大规模学习积累实战经验，战斗力爆棚。
>要回答为什么 attention 这么优秀？是因为它让模型开窍了，懂得了提纲挈领，学会了融会贯通。
>——阿里技术

## *Attention 的 N 种类型*

Attention 有很多种不同的类型：Soft Attention、Hard Attention、静态Attention、动态Attention、Self Attention 等等。下面就跟大家解释一下这些不同的 Attention 都有哪些差别。

![img](.\image\v2-7dfae91f2a921fd62eb0a1845fae2b52_1440w.webp)

**1. 计算区域**

根据Attention的计算区域，可以分成以下几种：

1）**Soft** Attention，这是比较常见的Attention方式，对所有key求权重概率，每个key都有一个对应的权重，是一种全局的计算方式（也可以叫Global Attention）。这种方式比较理性，参考了所有key的内容，再进行加权。但是计算量可能会比较大一些。

2）**Hard** Attention，这种方式是直接精准定位到某个key，其余key就都不管了，相当于这个key的概率是1，其余key的概率全部是0。因此这种对齐方式要求很高，要求一步到位，如果没有正确对齐，会带来很大的影响。另一方面，因为不可导，一般需要用强化学习的方法进行训练。（或者使用gumbel softmax之类的）

3）**Local** Attention，这种方式其实是以上两种方式的一个折中，对一个窗口区域进行计算。先用Hard方式定位到某个地方，以这个点为中心可以得到一个窗口区域，在这个小区域内用Soft方式来算Attention。

**2. 所用信息**

假设我们要对一段原文计算Attention，这里原文指的是我们要做attention的文本，那么所用信息包括内部信息和外部信息，内部信息指的是原文本身的信息，而外部信息指的是除原文以外的额外信息。

1）**General** Attention，这种方式利用到了外部信息，常用于需要构建两段文本关系的任务，query一般包含了额外信息，根据外部query对原文进行对齐。

比如在阅读理解任务中，需要构建问题和文章的关联，假设现在baseline是，对问题计算出一个问题[向量](https://link.zhihu.com/?target=https%3A//easyai.tech/ai-definition/vector/)q，把这个q和所有的文章词向量拼接起来，输入到[LSTM](https://link.zhihu.com/?target=https%3A//easyai.tech/ai-definition/lstm/)中进行建模。那么在这个模型中，文章所有词向量共享同一个问题向量，现在我们想让文章每一步的词向量都有一个不同的问题向量，也就是，在每一步使用文章在该步下的词向量对问题来算attention，这里问题属于原文，文章词向量就属于外部信息。

2）**Local** Attention，这种方式只使用内部信息，key和value以及query只和输入原文有关，在self attention中，key=value=query。既然没有外部信息，那么在原文中的每个词可以跟该句子中的所有词进行Attention计算，相当于寻找原文内部的关系。

还是举阅读理解任务的例子，上面的baseline中提到，对问题计算出一个向量q，那么这里也可以用上attention，只用问题自身的信息去做attention，而不引入文章信息。

**3. 结构层次**

结构方面根据是否划分层次关系，分为单层attention，多层attention和多头attention：

1）**单层Attention**，这是比较普遍的做法，用一个query对一段原文进行一次attention。

2）**多层Attention**，一般用于文本具有层次关系的模型，假设我们把一个document划分成多个句子，在第一层，我们分别对每个句子使用attention计算出一个句向量（也就是单层attention）；在第二层，我们对所有句向量再做attention计算出一个文档向量（也是一个单层attention），最后再用这个文档向量去做任务。

3）**多头Attention**，这是Attention is All You Need中提到的multi-head attention，用到了多个query对一段原文进行了多次attention，每个query都关注到原文的不同部分，相当于重复做多次单层attention：

![img](.\image\v2-132f774f1f144487c8f15c96661e63c5_1440w.webp)

最后再把这些结果拼接起来：

![img](.\image\v2-8a207952a127905dc4edc90ef4d1cd6a_1440w.webp)

**4. 模型方面**

从模型上看，Attention一般用在CNN和LSTM上，也可以直接进行纯Attention计算。

**1）CNN+Attention**

CNN的卷积操作可以提取重要特征，我觉得这也算是Attention的思想，但是CNN的卷积感受视野是局部的，需要通过叠加多层卷积区去扩大视野。另外，Max Pooling直接提取数值最大的特征，也像是hard attention的思想，直接选中某个特征。

CNN上加Attention可以加在这几方面：

a. **在卷积操作前做attention**，比如Attention-Based BCNN-1，这个任务是文本蕴含任务需要处理两段文本，同时对两段输入的序列向量进行attention，计算出特征向量，再拼接到原始向量中，作为卷积层的输入。

b. 在卷积操作后做attention，比如Attention-Based BCNN-2，对两段文本的卷积层的输出做attention，作为pooling层的输入。

c. **在pooling层做attention**，代替max pooling。比如Attention pooling，首先我们用LSTM学到一个比较好的句向量，作为query，然后用CNN先学习到一个特征矩阵作为key，再用query对key产生权重，进行attention，得到最后的句向量。

**2）LSTM+Attention**

LSTM内部有Gate机制，其中input gate选择哪些当前信息进行输入，forget gate选择遗忘哪些过去信息，我觉得这算是一定程度的Attention了，而且号称可以解决长期依赖问题，实际上LSTM需要一步一步去捕捉序列信息，在长文本上的表现是会随着step增加而慢慢衰减，难以保留全部的有用信息。

LSTM通常需要得到一个向量，再去做任务，常用方式有：

a. 直接使用最后的hidden state（可能会损失一定的前文信息，难以表达全文）

b. 对所有step下的hidden state进行等权平均（对所有step一视同仁）。

c. Attention机制，对所有step的hidden state进行加权，把注意力集中到整段文本中比较重要的hidden state信息。性能比前面两种要好一点，而方便可视化观察哪些step是重要的，但是要小心过拟合，而且也增加了计算量。

**3）纯Attention**

Attention is all you need，没有用到CNN/RNN，乍一听也是一股清流了，但是仔细一看，本质上还是一堆向量去计算attention。

# Transformer

## 1. Transformer 详解

## 1.1 高层Transformer

论文中的验证Transformer的实验室基于机器翻译的，下面我们就以机器翻译为例子详细剖析Transformer的结构，在机器翻译中，Transformer可概括为如图1：

![img](.\image\v2-1f6085e214b62d8293b2122a52489bff_1440w.webp)

Transformer的本质上是一个Encoder-Decoder的结构，那么图1可以表示为图2的结构：

![img](.\image\v2-5a252caa82f87920eadea2a2e93dc528_1440w.webp)

如论文中所设置的，编码器由6个编码block组成，同样解码器是6个解码block组成。与所有的生成模型相同的是，编码器的输出会作为解码器的输入，如图3所示：

![img](.\image\v2-c14a98dbcb1a7f6f2d18cf9a1f591be6_1440w.webp)

我们继续分析每个encoder的详细结构：在Transformer的encoder中，数据首先会经过一个叫做‘self-attention’的模块得到一个加权之后的特征向量 $Z$ ，这个 $Z$ 便是论文公式1中的 Attention(Q,K,V) ：
$$
Attention(Q, K, V) = softmax(\frac{QK^{T}}{\sqrt{d}})V
$$

> 正交核函数是在支持向量机（Support Vector Machines，SVM）中常用的一种核函数，它具有一些重要的性质。下面是正交核函数的主要性质：
>
> 正交性（Orthogonality）：正交核函数满足正交性质，即在特征空间中，它们相互正交。这意味着在计算特征空间中的内积时，正交核函数的乘积为零。正交性是正交核函数的核心特征，它有助于提高支持向量机的计算效率。
>
> 正定性（Positive Definiteness）：正交核函数是正定核函数的一种特殊情况。正定性是指对于任意非零向量组成的有限集合，其核矩阵都是半正定的。换句话说，正交核函数对应的核矩阵的特征值都是非负的。
>
> 可计算性（Computability）：正交核函数通常是基于输入空间中的内积计算而得到的。这些内积可以通过一些数值计算方法（例如多项式、高斯函数等）进行计算，因此正交核函数是可以计算的。
>
> 维度独立性（Dimension Independence）：正交核函数的计算结果与输入空间的维度无关。这意味着无论输入空间的维度是低维还是高维，正交核函数都能够提供有效的表示和分类能力。
>
> 映射能力（Mapping Capability）：正交核函数通过将输入空间中的数据映射到高维特征空间，使得原本线性不可分的数据在特征空间中变得线性可分。这种映射能力使得支持向量机能够处理复杂的非线性问题。
>
> 总的来说，正交核函数具有正交性、正定性、可计算性、维度独立性和映射能力等重要性质。这些性质使得正交核函数成为支持向量机中常用的核函数之一，并在分类和回归等任务中发挥重要作用。

第一次看到这个公式你可能会一头雾水，在后面的文章中我们会揭开这个公式背后的实际含义，在这一段暂时将其叫做 Z 。

得到 Z 之后，它会被送到encoder的下一个模块，即Feed Forward Neural Network。这个全连接有两层，第一层的激活函数是ReLU，第二层是一个线性激活函数，可以表示为：
$$
FNN(Z) = max(0, ZW+b) W + b
$$
Encoder的结构如图4所示：

![img](.\image\v2-89e5443635d7e9a74ff0b4b0a6f31802_1440w.webp)

Decoder的结构如图5所示，它和encoder的不同之处在于Decoder多了一个Encoder-Decoder Attention，两个Attention分别用于计算输入和输出的权值：

1. **Self-Attention**：当前翻译和已经翻译的前文之间的关系；
2. **Encoder-Decnoder Attention**：当前翻译和编码的特征向量之间的关系:

![img](.\image\v2-d5777da2a84e120846c825ff9ca95a68_1440w.webp)

## 1.2 输入编码

1.1节介绍的就是Transformer的主要框架，下面我们将介绍它的输入数据。如图6所示，首先通过Word2Vec等词嵌入方法将输入语料转化成特征向量，论文中使用的词嵌入的维度为 d_model=512 。

![img](.\image\v2-408fcd9ca9a65fdbf9d971cfd9227904_1440w.png)

在最底层的block中， x 将直接作为Transformer的输入，而在其他层中，输入则是上一个block的输出。为了画图更简单，我们使用更简单的例子来表示接下来的过程，如图7所示：

![img](.\image\v2-ff0f90ebee18dd909999bd3bee38fa45_1440w.webp)

**优点**：（1）虽然Transformer最终也没有逃脱传统学习的套路，Transformer也只是一个全连接（或者是一维卷积）加Attention的结合体。但是其设计已经足够有创新，因为其抛弃了在NLP中最根本的RNN或者CNN并且取得了非常不错的效果，算法的设计非常精彩，值得每个深度学习的相关人员仔细研究和品位。**（2）Transformer的设计最大的带来性能提升的关键是将任意两个单词的距离是1**，这对解决NLP中棘手的长期依赖问题是非常有效的。（3）Transformer不仅仅可以应用在NLP的机器翻译领域，甚至可以不局限于NLP领域，是非常有科研潜力的一个方向。（4）算法的并行性非常好，符合目前的硬件（主要指GPU）环境。

**缺点**：（1）粗暴的抛弃RNN和CNN虽然非常炫技，但是它也使模型丧失了捕捉局部特征的能力，RNN + CNN + Transformer的结合可能会带来更好的效果。（2）Transformer失去的位置信息其实在NLP中非常重要，而论文中在特征向量中加入Position Embedding也只是一个权宜之计，并没有改变Transformer结构上的固有缺陷。

# 位置信息

## 1. **绝对位置编码**

sin + cos 编码

## 2. **相对位置编码**

### 2.1. **Sinusoidal Position Encoding**

**位置pos+k的positional encoding可以被位置pos线性表示，反应其相对位置关系。**

### **2.2 . Complex embedding**

为了更好的让模型捕获更精确的相对位置关系，比如相邻，前序（precedence）等，ICLR 2020发表的文章《Encoding Word Oder In Complex Embeddings》使用了复数域的连续函数来编码词在不同位置的表示。

# GRU

![image-20231011160251988](.\image\image-20231011160251988.png)

![image-20231011160330083](.\image\image-20231011160330083.png)

# LSTM



![image-20231011154954555](.\image\image-20231011155116793.png)

### 候选记忆单元

![image-20231011155338182](.\image\image-20231011155338182.png)

### 记忆元

![image-20231011155006004](.\image\image-20231011155006004.png)

### 输出门

![image-20231011155027150](.\image\image-20231011155027150.png)

![image-20231011154901091](.\image\image-20231011154901091.png)

- 长短期记忆网络有三种类型的门：输入门、遗忘门和输出门。
- 长短期记忆网络的隐藏层输出包括“隐状态”和“记忆元”。只有隐状态会传递到输出层，而记忆元完全属于内部信息。
- 长短期记忆网络可以缓解梯度消失和梯度爆炸。

> GRU（Gated Recurrent Unit）和LSTM（Long Short-Term Memory）都是循环神经网络（RNN）中常用的两种变体，它们在解决序列数据建模问题上具有相似的目标，但在**内部结构**上有所不同。
>
> LSTM和GRU的共同点是它们都使用了门控机制来控制信息的流动，这使得它们能够在处理长序列时更好地捕捉和记忆长期依赖关系。
>
> LSTM是由Hochreiter和Schmidhuber于1997年提出的，它引入了三个门：**输入门（input gate）、遗忘门（forget gate）和输出门（output gate）**。输入门控制新信息的输入，遗忘门控制旧信息的遗忘，输出门控制输出的信息。LSTM通过这些门的组合和控制，能够有效地处理长期依赖关系，避免了传统RNN中的梯度消失问题。
>
> 相比之下，GRU是由Cho等人于2014年提出的一种简化的门控循环单元。**GRU只有两个门：更新门（update gate）和重置门（reset gate）**。更新门控制前一时刻的隐藏状态如何与当前时刻的输入结合，重置门控制前一时刻隐藏状态的遗忘程度。GRU通过这两个门的控制，能够在一定程度上实现LSTM的功能，同时减少了参数量和计算开销。
>
> 从使用上来看，LSTM和GRU在处理序列数据时往往能够取得类似的效果。但由于GRU的简化结构，它在计算上更加高效，参数较少，因此在某些资源受限的情况下，GRU可能是更好的选择。而LSTM则更适合在需要更好的建模能力和长期记忆的情况下使用。
>
> 总的来说，LSTM和GRU是两种常用的循环神经网络变体，它们在内部结构上有所不同，但都能有效地处理序列数据。选择使用哪种结构取决于具体的任务需求、数据特点和计算资源等因素。

# BERT

从现在的大趋势来看，使用某种模型预训练一个语言模型看起来是一种比较靠谱的方法。从之前AI2的 ELMo，到 OpenAI的fine-tune transformer，再到Google的这个BERT，全都是对预训练的语言模型的应用。

## BERT这个模型与其它两个不同的是：

> 1、它在训练双向语言模型时以减小的概率把少量的词替成了Mask或者另一个随机的词。我个人感觉这个目的在于使模型被迫增加对上下文的记忆。至于这个概率，我猜是Jacob拍脑袋随便设的。
> 2、增加了一个预测下一句的loss。这个看起来就比较新奇了。

## BERT模型具有以下两个特点：

第一，是这个模型非常的深，12层，并不宽(wide），中间层只有1024，而之前的Transformer模型中间层有2048。这似乎又印证了计算机图像处理的一个观点——深而窄 比 浅而宽 的模型更好。

第二，MLM（Masked Language Model），同时利用左侧和右侧的词语，这个在ELMo上已经出现了，绝对不是原创。用这篇论文的方法去做Masking，相信BRET的能力说不定还会有提升。

**1、论文的主要贡献**

> （1）证明了双向预训练对语言表示的重要性。与之前使用的单向语言模型进行预训练不同，BERT使用遮蔽语言模型来实现预训练的深度双向表示。
> （2）论文表明，预先训练的表示免去了许多工程任务需要针对特定任务修改体系架构的需求。 BERT是第一个基于微调的表示模型，它在大量的句子级和token级任务上实现了最先进的性能，强于许多面向特定任务体系架构的系统。
> （3）BERT刷新了11项NLP任务的性能记录。本文还报告了 BERT 的模型简化研究（ablation study），表明模型的双向性是一项重要的新成果。相关代码和预先训练的模型将会公布在goo.gl/language/bert上。

任务1: Masked LM ===> 双向训练

任务2：下一句预测 ===> 在为了训练一个理解句子的模型关系，预先训练一个二进制化的下一句测任务，这一任务可以从任何单语语料库中生成。具体地说，当选择句子A和B作为预训练样本时，B有50％的可能是A的下一个句子，也有50％的可能是来自语料库的随机句子。团队完全随机地选择了NotNext语句，最终的预训练模型在此任务上实现了97％-98％的准确率。