# 学习网址
## 视频:
https://www.bilibili.com/video/BV1i54y1m7tw?spm_id_from=333.1007.top_right_bar_window_history.content.click
## csdn:
https://blog.csdn.net/liandanba/article/details/122726231
## gitee
https://gitee.com/loading123/opencv_tutorial_data
https://gitee.com/opencv_ai/opencv_tutorial_data

# opencv知识点：
创建和操作综合人工神经网络 - dnn::Net类
读取以TensorFlow框架格式存储的网络模型 - readNetFromTensorflow
从图像创建4维blob - blobFromImage
设置网络的新输入值- Net::setInput
运行正向传递以计算指定层的输出 - Net::forward

# API
## dnn::Net类
	创建和操作综合人工神经网络
		神经网络表示为有向无环图 (DAG)，其中顶点是层实例，边指定层输入和输出之间的关系。
		每个网络层在其网络内都有唯一的整数id 和唯一的字符串名称。LayerId 可以存储图层名称或图层ID。
		此类支持其实例的引用计数，即副本指向同一个实例。
## readNetFromTensorflow
	读取以TensorFlow框架格式存储的网络模型
		共2个参数
			第1个参数 pb文件路径
			第2个参数 pbtxt文件路径
## blobFromImage
	从图像创建4维blob（斑点，深度学习相关知识）
		共7个参数
			第1个参数 输入
			第2个参数 图像空间大小（默认1.0，即图像仍保持在0~255色彩空间）
			第3个参数 size
			第4个参数 均值
			第5个参数 是否交换RB通道（默认false）
			第6个参数 调整图像大小后是否剪切（默认false）
			第7个参数 输出的blob深度（默认CV_32F）

	returns
		按照NCHW(数量，通道，高度，宽度)顺序的4维Mat，blob就是这个4维Mat

## setInput
	设置网络的新输入值
		共4个参数
			第1个参数 输入斑点
			第2个参数 输入层名称（默认为空“”）
			第3个参数 可选的标准化比列
			第4个参数 可选的平均值

## forward
	运行正向传递以计算名为 outputName 的层的输出。
		共1个参数
			第1个参数 需要输出的层的名称
	returns
		返回也有四个值
			第1个维度 表示有多少张图像，并且每个图像有一个编号。imageId
			第2个维度 图像的批次。batchId
			第3个维度 有多少个框（行）
			第4个维度 每个框有7个值（列）
							前两个值 标明类型 + index
							第3个值 得分（得分越高，越有可能是人脸）
							后四个值 矩形左上角和右下角的坐标

						


