/**
文件描述:	无向图的模板类实现
作者:	吴云鹏
编写时间:	2017-6-28
**/
/**
无向图的元素类型必须支持如下几个特性，否则无法通过编译
1)要支持std::cin >>操作
2)具备默认构造函数
3)具有复制构造函数
4)具有自定义的 operator<操作符函数
**/
#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>
#include <assert.h>
template <class ElementType>
class Graph{
public:
	Graph(int vertex_number);//创建一个含有V个顶点但不含有边的图
	Graph(std::string file_name);//读入一个存放图的数据的文件来构造图
	
	~Graph(){
		if (!m_adjacency_table_.empty())
		{
			for (auto iter = m_adjacency_table_.begin();iter != m_adjacency_table_.end();++iter)
			{
				Vertex * head = iter->second;
				while (head)
				{
					Vertex * next_ptr_vertex = head->next_vertex_;
					delete head;
					head = next_ptr_vertex;
				}
				//std::cout << '\n';
			}
		}
		std::cout << "内存清空完毕\n";
	};//图的析构函数
	inline std::vector<ElementType> GetAdjacentVertexNumbers(const ElementType & element_value) const 
	{
		auto iter = m_adjacency_table_.find(element_value);
#ifdef _DEBUG
		assert(iter != m_adjacency_table_.end());
#endif // _DEBUG
		std::vector<ElementType> res_vec;
		Vertex * head = iter->second;
		while(head)
		{
			res_vec.push_back(head->m_vertex_);
			head = head->next_vertex_;
		}
		res_vec.erase(res_vec.begin());
		return res_vec;
	};
	int GetVertexNumbers() const ;//求出这个无向图的顶点个数
	int GetEdgeNumbers() const ;//求出这个无向图的边数
	inline ElementType GetVertexElementValue(int index) const //获得邻接表中索引值从0到最后对应的顶点值
	{   
		auto iter = m_adjacency_table_.begin();
		for(int i = 0;i < index;++i)
			iter++;
		return iter->first;
	};
	void AddEdge(const ElementType & edge_begin_vertex_value,const ElementType & edge_end_vertex_value);//添加一条edge_begin_vertex_value->edge_end_vertex_value的边
	inline void SetVertexMarked(const ElementType & element_value)//标记值为element_value的顶点
	{
		m_mark_vertex_vec_.push_back(element_value);
	}
	static int GetDegree(const Graph & graph,const ElementType & vertex_value);//求出无向图graph中值为vertex_value的顶点的度数
	static int GetMaxDegree(const Graph & graph);//求出无向图graph中最大度数
	static int GetMinDegree(const Graph & graph);//求出无向图graph中最小度数
	static int GetAvergeDegree(const Graph & graph);//求出无向图graph中平均度数
	static int GetNumberOfSelfLoops(const Graph & graph)  ;//计算自环的个数
	static void DepthFirstSearch(const Graph & graph);//深度优先遍历图的所有顶点
private:
	struct Vertex{
		Vertex(const ElementType & element_value,Vertex * ptr_next_vertex = nullptr):m_vertex_(element_value),next_vertex_(ptr_next_vertex)
		{
		};
		~Vertex()
		{
			//std::cout << "<--" << m_vertex_ << "-->被析构\n";
		};
		ElementType m_vertex_;
		Vertex * next_vertex_;
	};
	Graph(const Graph & graph);//禁用复制构造函数
	Graph operator=(const Graph & graph);//禁用赋值操作函数
	std::map<ElementType,Vertex *> m_adjacency_table_;//图的邻接表
	std::vector<ElementType> m_mark_vertex_vec_;//深度优先遍历时存储已被标记过的顶点值容器

};

/**
第一种构造函数形式,构造无边的无向图
输入参数: 顶点的个数为vertex_number
**/
template <class ElementType>
Graph<ElementType>::Graph(int vertex_number)
{
	std::cout << "输入所有顶点的值\n";
	for (int i = 0;i < vertex_number;++i)
	{   
		ElementType element_obj;
		std::cin >> element_obj;
		Vertex * ptr_vertex = new Vertex(element_obj);//记住要析构函数中释放掉
		m_adjacency_table_[element_obj] = ptr_vertex;
	}
	std::cout << "构造无向图完毕\n"; 
}

/**
第二种构造函数形式,通过txt文件导入
输入参数: txt文件名为file_name

example:
txt文件的布局如下:
------------------------
顶点总数
边总数
a b 每一条边的首尾顶点值  
c d
...
...
e f
------------------------
**/
template <class ElementType>
Graph<ElementType>::Graph(std::string file_name)
{
	int vertex_sum_number = 0;
	std::ifstream file_in_stream(file_name);
	file_in_stream >> vertex_sum_number;
	int edge_sum_number = 0;
	file_in_stream >> edge_sum_number;
	while(file_in_stream.peek() != EOF)
	{
		ElementType begin_element_obj,end_element_obj;
		file_in_stream >> begin_element_obj >> end_element_obj;
		Graph<ElementType>::AddEdge(begin_element_obj,end_element_obj);
	}
	if (m_adjacency_table_.size() != vertex_sum_number)
	{
		std::cerr << "文件格式不正确\n";
	}
	else
		std::cout << "构造无向图完毕\n"; 
};

/**
求出无向图的顶点数
**/
template <class ElementType>
int Graph<ElementType>::GetVertexNumbers() const 
{
	return m_adjacency_table_.size();
}

/**
求出无向图的边数,时间复杂度不是常数
**/
template <class ElementType>
int Graph<ElementType>::GetEdgeNumbers() const
{   
	int edge_counts = 0;
	for (auto iter = m_adjacency_table_.begin();iter != m_adjacency_table_.end();++iter)
	{
		Vertex * head = iter->second;
		while(head)
		{
			edge_counts++;
			head = head->next_vertex_;
		}
		edge_counts--;
	}
	return edge_counts/2;
}

/**
求出无向图graph中值为vertex_value的顶点的度数
**/
template<class ElementType>
int Graph<ElementType>::GetDegree(const Graph & graph,const ElementType & vertex_value)
{
	return (graph.GetAdjacentVertexNumbers(vertex_value)).size();
}


/**
求出无向图graph中最大度数
**/
template<class ElementType>
int Graph<ElementType>::GetMaxDegree(const Graph & graph)
{   
	if (graph.GetVertexNumbers() == 0)
		return 0;
	int max_degree = Graph<ElementType>::GetDegree(graph,graph.GetVertexElementValue(0));
	for(int i = 1;i < graph.GetVertexNumbers();++i)
	{   
		int degree = Graph<ElementType>::GetDegree(graph,graph.GetVertexElementValue(i));
		if (max_degree < degree )
			max_degree = degree;
	}
	return max_degree;
}

/**
求出无向图graph中最小度数
**/
template<class ElementType>
int Graph<ElementType>::GetMinDegree(const Graph & graph)
{   
	if (graph.GetVertexNumbers() == 0)
		return 0;
	int min_degree = Graph<ElementType>::GetDegree(graph,graph.GetVertexElementValue(0));
	for(int i = 1;i < graph.GetVertexNumbers();++i)
	{   
		int degree = Graph<ElementType>::GetDegree(graph,graph.GetVertexElementValue(i));
		if (min_degree > degree )
			min_degree = degree;
	}
	return min_degree;
}

/**
求出无向图graph中平均度数
**/
template<class ElementType>
int Graph<ElementType>::GetAvergeDegree(const Graph & graph)
{
	float sum_degree = 0;
	for (int i = 0;i < graph.GetVertexNumbers();++i)
	{
		sum_degree += Graph<ElementType>::GetDegree(graph,graph.GetVertexElementValue(i));
	}
	return sum_degree/graph.GetVertexNumbers();
}

/**
计算自环的个数
**/
template<class ElementType>
int Graph<ElementType>::GetNumberOfSelfLoops(const Graph & graph)
{   
	int self_loop_numbers = 0;
	for(int i = 0;i <graph.GetVertexNumbers();++i)
	{    
		ElementType tmp = graph.GetVertexElementValue(i);
		std::vector<ElementType> adjacent_vertex_value_vec = graph.GetAdjacentVertexNumbers(tmp);
		if (std::find(adjacent_vertex_value_vec.begin(),adjacent_vertex_value_vec.end(),tmp) != adjacent_vertex_value_vec.end())
		{
			 self_loop_numbers++;
		}
	}
	return self_loop_numbers;
}

/**
添加一条edge_begin_vertex_value->edge_end_vertex_value的边
**/
template<class ElementType>
void Graph<ElementType>::AddEdge(const ElementType & edge_begin_vertex_value,const ElementType & edge_end_vertex_value)
{   
	auto iter = m_adjacency_table_.find(edge_begin_vertex_value);
	Vertex * ptr_begin_vertex = nullptr;
	Vertex * ptr_end_vertex = nullptr;
	Vertex * insert_vertex = nullptr;
	if(iter == m_adjacency_table_.end())//如果开始结点是新的节点
	{  
		ptr_begin_vertex = new Vertex(edge_begin_vertex_value);//记住要析构函数中释放掉
		m_adjacency_table_[edge_begin_vertex_value] = ptr_begin_vertex;
	}
	else//如果开始节点已经存在
	{
		ptr_begin_vertex = iter->second;
	}
	insert_vertex = new Vertex(edge_end_vertex_value);//等待插入的顶点
	Vertex * tmp = ptr_begin_vertex->next_vertex_;
	ptr_begin_vertex->next_vertex_ = insert_vertex;
	insert_vertex->next_vertex_ = tmp;

	//尾部顶点是否已经存在图中
	iter = m_adjacency_table_.find(edge_end_vertex_value);
	if (iter == m_adjacency_table_.end())
	{   
		ptr_end_vertex = new Vertex(edge_end_vertex_value);
		m_adjacency_table_ [edge_end_vertex_value] = ptr_end_vertex; 
	}
	else
	{
		ptr_end_vertex = iter->second;
	}
	insert_vertex = new Vertex(edge_begin_vertex_value);//等待插入的顶点
	tmp = ptr_end_vertex->next_vertex_;
	ptr_end_vertex->next_vertex_ = insert_vertex;
	insert_vertex->next_vertex_ = tmp;
}

/**
深度优先遍历图的所有顶点
**/
template<class ElementType>
void Graph<ElementType>::DepthFirstSearch(const Graph & graph)
{
	if (graph.GetVertexNumbers() == 0)
		return;
	else
	{
		
	}
}
#endif
