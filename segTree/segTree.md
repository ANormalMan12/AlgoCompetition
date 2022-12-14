# 区间树

## 注意

* 一定要确定是区间型还是点型.并且一定要确保[l,mid],[mid+1,r]这样点的分类是正确的。

## segTreePoint1.cpp

此时,pDC仅在被查询的时候才下降，但对于情况2来说，这是不行的，在add期间也要对pDC进行下降，因为pDC所影响的sum值也会因reset而变化，如果根下方的结点整体reset，其对于pDC的影响也是无法预估的。


## 线段树：区间增加与覆盖

这道题的关键是在维护区间加操作的基础上，新增维护区间最大最小值（如果只引入这个的话也很简单）。

但它又引入了较难的区间值重置操作。如果只用课件里的代码，难以解决。

why：

reset造成的变化是不可预料的。

这要求min.max,sum只能通过回溯的方式被更新。

因此，在结点内dC,sum的基础上，引入min,max,reset等懒惰标记。

由于节点的reset标记有时处于未标记态，所以要用一个输入数据不可能用的值，本处使用的是long long 的最小值。

## 规则

* 与上一题不同，reset,pDC在更新时会直接改变pSum,pMin,pMax，但仍然不会对对下方结点有影响，这是为了回溯的方便。
* 由于上一条，在下降时，up和pDC都不会对pSum造成影响，它们会在下方制造影响，并通过回溯来影响pSum,min,max。
* 如果下降的reset不是NoVal，那么exactly match的时候，up会被无视（因为整个区间都被重置了）。

在向下传播的的时候，
* 如果传播的reset=NoVal，那么正常下传。
* 如果传播的reset!=NoVal，那么在用reset对区间进行覆盖时(exactly match)，up的影响应该被无效化。

## 懒惰结点的目的是什么呢

exactly match

其实回溯也是很好实现的。
