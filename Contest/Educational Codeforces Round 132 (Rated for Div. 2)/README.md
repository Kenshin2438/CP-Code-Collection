## A Three Doors
...

## B Also Try Minecraft
...

## C Recover an RBS
构造

先补全`(`使得`(`数目到$\frac{n}{2}$，再是`)`。将最右的变成`(`的`?`改成`)`，最左的变成`)`的`?`改成`(`，贪心易知，如果有多种办法，这种必然是其中之一。

## D Rorororobot
RMQ

## E XOR Tree
启发式合并

不要写`set`的`=`赋值，不要写`set`的`=`赋值，不要写`set`的`=`赋值。

## F Multiset of Strings
NTT

长度为$n$，$c_i$限制为$k$时，（不同容量限制构成）答案序列的生成函数如下：
$$
F_{n,k}(x) = \sum_{i=0}^{2k}ans[i]\times x^i
$$
长度为$n+1$，同时$k$不变的条件下。相较于之前长度为$n$只增加了一个`0/1`。
易知有：$[f]F_{n+1,k}(x)=\sum_{i+j=f}G_0(i) \times G_1(j)$