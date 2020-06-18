<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
    <h1>需求分析报告</h1>
    <h2>一、课题内容分析</h2>
    <p> 
        用无向网表示你所在学校的校园景点平面图，图中顶点表示主要景点，存放景点的编号、名称、简介等信息，图中的边表示景点间的道路，存放路径长度等信息。要求能够回答有关景点介绍、游览路径等问题。
    </p>
        <p>*查询各景点的相关信息。</p>
        <p>*查询图中任意两个景点间的最短路径。</p>
        <p>*查询图中任意两个景点间的所有路径。</p>
        <p>*增加、删除、更新有关景点和道路的信息。</p>
        <br><br>
        <h2>二、需求分析</h2>
<h3>1、所需知识点</h3>
   <p>*图的各种遍历算法</p>
   <p>*单源最短路径(Dijkstra算法)</p>
   <p>*图的储存结构(链式前向星)</p>
   <p>*文件的读取存储操作</p>
   <p>*界面交互</p>
<h3>2、数据结构</h3>
       <p>本课题用到的数据结构是图的数据结构，其中用到的是链式前向星作为储存结构</p> 
<p>typedef struct Edge {</p>
<p>        				int to;           //到达点</p>
<p>           			int w;            //边权值</p> 
<p>            			int next;         //当前起点的下一条边的起始edge的号</p> 
<p>         }Edge;</p>
<p>        int head[maxn]; </p> 
<p>         //顶点，边数</p>
<p>        int v, e;</p>
<h3>3、基本算法的实现</h3>
      <p>searchLocation();			//查询景点信息</p>       
      <p>shortPath();				//打印两点最短路径</p>       
      <p>dfsAllPath();				//遍历两点间的所有路径</p>           
      <p>addNode(); 				//增加景点</p>
      <p>deleteNode();				//删除景点</p>  
      <p>updateNode();				//更新道路信息，景点信息</p>
      <p>systemExit(&quit); 		//退出系统</p>
      <p>printMap();				//打印校园地图</p>  
      <br><br>
 <h2>三、开发人员</h2>
   <p>*独立开发</p>
</body>
</html>
