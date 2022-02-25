## Charpt1 你好，并发世界!

#### 使用并发的原因
-	分离关注点
-	性能： (a) 任务并行(task parallelism)： 将单个任务分成几部分并行运行，各个部分间可能存在依赖 (b) 数据并行(data parallelism)： 每个线程在不同数据块上执行相同的操作


#### 什么时候不使用并发

- 操作系统资源有限，每个线程都有独立的堆栈；运行越多的线程，就需要越多的上下文切换(上下文切换需要时间），可以考虑使用线程池


#### 历史
-	C++98不承认线程存在，以及内存模型。
- C++11/C++14/C++17对并发的支持。