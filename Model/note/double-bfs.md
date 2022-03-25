# 双向BFS

## bfs()
1. 将起始节点放入队列q1,  将目的节点放入队列q2

2. 当两个队列都未空时，作如下循环

    (1) 如果队列q1里的未处理节点比q2中的少（即tail[0]-head[0] < tail[1]-head[1]),则扩展（expand()）队列q1

    (2) 否则扩展（expand()）队列q2 (即tail[0]-head[0] >= tail[1]-head[1]时)

3. 如果队列q1未空，循环扩展（expand()）q1直到为空

4. 如果队列q2未空，循环扩展（expand()）q2知道为空

## expand()

取队列qi的头结点H

对头节点H的每一个相邻节点adj，作如下循环

    1. 如果adj已经在队列qi之前的某个位置出现，则抛弃节点adj

    2. 如果adj在队列qi中不存在[函数 isduplicate(i)]

        (1) 将adj放入队列qi

        (2) 如果adj 在队列(q(1-i))，也就是另外一个队列中出现[函数 isintersect()]

            输出 找到的路径  