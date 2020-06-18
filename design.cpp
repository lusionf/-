#include<iostream>
#include <algorithm>
#include<string.h>
#include<queue>
#include<stack>
#include<fstream>

using namespace std;

//景点信息储存
typedef struct Node
{
    int num;
    char name[20];
    char intro[1000];
}Node;

//链式前向星，本质邻接表
typedef struct Edge {
    int to;           //到达点
    int w;            //边权值
    int next;         //当前起点的下一条边的起始edge的序号
}Edge;

//初始化常量
const int maxn = 100;
const int INF = 0X3f3f3f3f;

//顶点，边数
int v, e; 

//全局变量准备
int visted[maxn];     
int parent[maxn];   
int dist[maxn]; 
int cnt;        
int head[maxn]; 
Edge edge[maxn];
Node node[maxn];
int sta[maxn];
int top;
int countRoads;

typedef pair<int, int> iPair; 


//初始化全局变量
void InitVa(){
    memset(sta,-1,sizeof(sta));
    memset(parent,-1,sizeof(parent));
    memset(dist, INF, sizeof(dist));
    memset(visted,0,sizeof(visted));
    top = -1;
    countRoads = 0;
}


void adde(int from, int to, int w) { //添加边
    edge[cnt].to = to;
    edge[cnt].w = w;
    edge[cnt].next = head[from];  //使要添加的边的指向下一条边的变量存下当前head中对应点的数
    head[from] = cnt++;   //记下当前边在edge数组的位置，并且作为头传递给head数组

    edge[cnt].to = from;
    edge[cnt].w = w;
    edge[cnt].next = head[to];  //使要添加的边的指向下一条边的变量存下当前head中对应点的数
    head[to] = cnt++;   //记下当前边在edge数组的位置，并且作为头传递给head数组
}

//初始化
void init() { 
        InitVa();
        cnt = 0;
        memset(head, -1, sizeof(head));       //head初始化后不会发生变化
        ifstream myfile("map2.txt"); 
        if(myfile.is_open()){
		      myfile >> v >> e;
          for(int i = 0; i < v; i++){
		      myfile >> node[i].num >> node[i].name >> node[i].intro;
        }
	        for(int k = 0; k < e; k++){	
              int from, to, next;
              myfile >> from >> to >> next;
	      	    adde(from,to,next);
      }
          myfile.close();   
    }
	    else{
            cout << "没有地图信息!";
      }

}




// 主菜单
int menu() {
	int s;
	printf("\t\t                ┌───────────────────┐                \n");
	printf("\t\t┌──────├── 欢迎使用攀枝花学院导游系统 ──┤──────┐\n");
	printf("\t\t│              └───────────────────┘              │\n");
	printf("\t\t│                                                                               │\n");
	printf("\t\t│                                                                      │\n");
	printf("\t\t│   ┌────────────┐        ┌────────────┐   │\n");
	printf("\t\t│   1.攀枝花学院景点信息查询2.两景点间最短路径查询   │\n");
	printf("\t\t│   └────────────┘        └────────────┘   │\n");
	printf("\t\t│                                                                      │\n");
	printf("\t\t│   ┌────────────┐        ┌────────────┐   │\n");
	printf("\t\t│   3.两景点间所有路径查询   4.增加景点信息    │\n");
	printf("\t\t│   └────────────┘        └────────────┘   │\n");
	printf("\t\t│                                                                      │\n");
	printf("\t\t│   ┌────────────┐        ┌────────────┐   │\n");
	printf("\t\t│   │ 5.删除景点信息         6.更改景点信息    │\n");
	printf("\t\t│   └────────────┘        └────────────┘   │\n");
  printf("\t\t│   ┌────────────┐        ┌────────────┐   │\n");
	printf("\t\t│             7.退出校园导游系统    │\n");
	printf("\t\t│   └────────────┘        └────────────┘   │\n");
	printf("\t\t│                                                                      │\n");
	printf("\t\t└───────────────────────────────────┘\n\n");
	printf("\t\t请根据你的需求选择操作：");
	scanf("%d", &s);
	printf("\n\n");
	return s;
}


// 校园景点图的显示
void printMap() {
	printf("\n                                           『攀枝花学院地图』\n\n\n\n");
	printf("                                         ===◎(5)运动场===                            \n");
	printf("	                                  		                   ===◎(7)第一教学楼===                       \n");
	printf("	                  ===◎(4)图书馆===               \n");
	printf("	                                                ===◎(6)第二教学楼===                \n");
	printf("	                                                                            		===◎(8)篮球场===\n");
	printf("	                                                     		\n");
	printf("	            ===◎(3)会堂===                                               ===◎游泳馆(9)=== \n");
	printf("	                                                             \n");
	printf("	                           ===◎(2)校历史展览馆===		                                            \n");
	printf("	                                                     		\n");
	printf("           ===◎(1)西 门===                                                                              \n");
	printf("                    			  ===◎(10)学院超市===                                                \n\n");
}

// 查找景点信息

int judgeInput(int num){
  if(num > v || num < 0 || node[num-1].num == -1){
        return 0;
  }
    return 1;
}

void searchLocation() {
	int s;
  cout << "请输入你要查找的景点编号：";
	cin >> s;
  cout << endl;

  while(judgeInput(s)){
    
    cout << "景点名称 :" << node[s-1].name << endl << endl;
	  cout << "景点简介 :" << node[s-1].intro << endl << endl;

    cout << "请输入你要查找的景点编号：";
	  cin >> s;
    cout << endl;
  }
    cout << "景点不存在，或者景点已被移除" << endl;
}

// void test_parent(){
//     for(int i = 0; i < 5; i++){
//       cout << parent[i] << '\t';
//     }
//   }

// void test_distance(){
//     for(int i = 0; i < 5; i++){
//       cout << dist[i] << '\t';
//     }
//   }

//两点间的最短路径
void dijkstra(int from){
     
        //优先队列准备
        priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

       //距离，头
        pq.push(make_pair(0,from));
        dist[from] = 0;

        parent[from] = -1;
 
        while(!pq.empty()){
          
            from = pq.top().second;
            visted[from] = 1;
            pq.pop(); 
            for(int i = head[from]; ~i; i = edge[i].next){

              if(!visted[edge[i].to]){
             
              int v = edge[i].to;
              int weight = edge[i].w;

              if(dist[v] > dist[from] + weight){
                
                parent[v] = from;
                dist[v] = dist[from] + weight;
                pq.push(make_pair(dist[v], v));
              }
            }   
        }
      }
}

//打印两点的最短路径
  void shortPath(){
        InitVa();
        int from, to;
        cout << "请输入from->to，景点编号: " << endl;
  
        cin >> from >> to;
        if(!judgeInput(from) || !judgeInput(to)){
                cout << "景点编号输入错误~" << endl;
                return;
        }
        --from;
        --to;
        dijkstra(from);
        
        for(int i = to; ~i; i = parent[i]){
          if(i == from){
            sta[++top] = i; //
            cout << "从" << node[from].name << "到" << node[to].name << "的最短路径如下" << endl << endl;
            for(int i = top; i >= 0; i--){
              cout << node[sta[i]].num << " " << node[sta[i]].name  << "->";
            }
            cout << "最短距离是:" << dist[to] << endl;
              return;
          };
            sta[++top] = i;       
        }
        cout << "抱歉，这期间没有路径" << endl;
  }



void DFS(int from, int to){ 
        int i = head[from];
        visted[from] = 1;
        sta[++top] = from;
        if(from == to){
          cout <<"这是第" << ++countRoads << "条路径 :";
          for(int i = 0; i <= top; i++){
              cout << node[sta[i]].name << " -> ";
          }
          cout << endl << endl;
          top--;
          visted[to] = 0;
          return;
        }
        for( ; ~i; i = edge[i].next){
            if(!visted[edge[i].to]){
              DFS(edge[i].to,to);
            }
        } 
        if(i == -1) {
          top--;
          visted[from] = 0;
        }   
}


void dfsAllPath(){
      InitVa();
      int from, to;
        cout << "请输入from->to，景点编号: " << endl;
  
        cin >> from >> to;
        if(!judgeInput(from) || !judgeInput(to)){
                cout << "景点编号输入错误~";
                return;
        }
        --from;
        --to;
      DFS(from,to);
}


void addNode(){
      int from,to,w;
      cout << "请输入景点编号, 景点名字, 景点介绍";
      cin >> node[v].num >> node[v].name >> node[v].intro;
      ++v;
      cout << "请输入要增加的边: from->to, weight" << endl;
      cin >> from >> to >> w;
      --from;
      --to;
      adde(from,to,w);
}

void deleteedge(int from, int to){
      for(int i = head[from];~i ; i = edge[i].next){
            if(edge[head[from]].to == to){
            head[from] = edge[head[from]].next;
            break;
      }
            if(edge[edge[i].next].to == to){
                edge[i].next = edge[edge[i].next].next;
                break;
            }
      }
      for(int i = head[to]; ~i ; i = edge[i].next){
            if(edge[head[to]].to == from){
              head[to] = edge[head[to]].next;
              break;
            }
            if(edge[edge[i].next].to == from){
                edge[i].next = edge[edge[i].next].next;
                break;
            }
      }

}

void deleteNode(){
      int num;
      cout << "请输入要删除的景点编号";
      cin >> num;

      node[num-1].num = -1; //judge
      for(int i = head[num-1];~i; i = edge[i].next){
          deleteedge(num-1,edge[i].to);
      }
      head[num - 1] = -1;
}

bool isUpdateName(){
    cout << "是否更改景点名称: " << endl;
    bool j;
    
    cout << "Yes: 1, No: 0" << endl;
    cin >> j;
    return j;
}

bool isUpdateIntro(){
    cout << "是否更改景点介绍: " << endl;
    bool j;
    cout << "Yes: 1, No: 0" << endl;
    cin >> j;
    return j;
}

bool isAddWay(int *from, int *to, int *w){
    cout << "是否增加道路信息: " << endl;
    bool j;
    cout << "Yes: 1, No: 0" << endl;
    cin >> j;
    if(j){
    cout << "请输入道路信息 from -> to, weight" << endl;
    cin >> *from >> *to >> *w;
    }
    return j;
}

bool isDeleteway(int *from, int *to){
    cout << "是否删除道路信息: " << endl;
    bool j;
    cout << "Yes: 1, No: 0" << endl;
    cin >> j;
    if(j){
    cout << "请输入道路信息 from -> to" << endl;
    cin >> *from >> *to;
    }
    return j;

}



void updateNode(){
     int num;
     int i, j, k;
     char name[20];
     char intro[1000];
      cout << "请输入要更新的景点编号" << endl;
      cin >> num;
      if(isUpdateName()){
        cin >> name;
        strcpy(node[num-1].name,name);
      }
      if(isUpdateIntro()){
        cin >> intro;
       strcpy(node[num-1].intro,intro);
      }
      if(isAddWay(&i, &j, &k)){
            adde(i-1,j-1,k);
         }
      if(isDeleteway(&i,&j)){
            deleteedge(i-1,j-1);
      }   
}

void systemExit(int *quit) {
	*quit = 1;
	printf("\t\t欢迎使用，期待下次光临\n\n");
}

int main(){
    init();
	  int quit = 0;                                                                                                                  
		while (!quit) {                                                         
			switch (menu()) {                                                   
			case 1:system("cls"); printMap(); searchLocation(); break;         
			case 2:system("cls"); printMap(); shortPath(); break;        
			case 3:system("cls"); printMap(); dfsAllPath(); break;          
			case 4:system("cls"); printMap(); addNode(); break;  
			case 5:system("cls"); printMap(); deleteNode(); break; 
      case 6:system("cls"); printMap(); updateNode(); break; 
			case 7:system("cls"); printMap(); systemExit(&quit); break; 
			default:printf("\t\t\t\t\t错误！没有该选项对应的操作。\n\n");
		}
			system("pause");
			system("cls");                                                           /*清屏*/
	}
	    system("pause");
}

