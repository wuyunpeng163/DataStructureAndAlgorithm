/**
�ļ�����:	����ͼ��ģ����ʵ��
����:	������
��дʱ��:	2017-6-28
**/
/**
����ͼ��Ԫ�����ͱ���֧�����¼������ԣ������޷�ͨ������
1)Ҫ֧��std::cin >>����
2)�߱�Ĭ�Ϲ��캯��
3)���и��ƹ��캯��
4)�����Զ���� operator<����������
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
	Graph(int vertex_number);//����һ������V�����㵫�����бߵ�ͼ
	Graph(std::string file_name);//����һ�����ͼ�����ݵ��ļ�������ͼ
	
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
		std::cout << "�ڴ�������\n";
	};//ͼ����������
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
	int GetVertexNumbers() const ;//����������ͼ�Ķ������
	int GetEdgeNumbers() const ;//����������ͼ�ı���
	inline ElementType GetVertexElementValue(int index) const //����ڽӱ�������ֵ��0������Ӧ�Ķ���ֵ
	{   
		auto iter = m_adjacency_table_.begin();
		for(int i = 0;i < index;++i)
			iter++;
		return iter->first;
	};
	void AddEdge(const ElementType & edge_begin_vertex_value,const ElementType & edge_end_vertex_value);//���һ��edge_begin_vertex_value->edge_end_vertex_value�ı�
	inline void SetVertexMarked(const ElementType & element_value)//���ֵΪelement_value�Ķ���
	{
		m_mark_vertex_vec_.push_back(element_value);
	}
	static int GetDegree(const Graph & graph,const ElementType & vertex_value);//�������ͼgraph��ֵΪvertex_value�Ķ���Ķ���
	static int GetMaxDegree(const Graph & graph);//�������ͼgraph��������
	static int GetMinDegree(const Graph & graph);//�������ͼgraph����С����
	static int GetAvergeDegree(const Graph & graph);//�������ͼgraph��ƽ������
	static int GetNumberOfSelfLoops(const Graph & graph)  ;//�����Ի��ĸ���
	static void DepthFirstSearch(const Graph & graph);//������ȱ���ͼ�����ж���
private:
	struct Vertex{
		Vertex(const ElementType & element_value,Vertex * ptr_next_vertex = nullptr):m_vertex_(element_value),next_vertex_(ptr_next_vertex)
		{
		};
		~Vertex()
		{
			//std::cout << "<--" << m_vertex_ << "-->������\n";
		};
		ElementType m_vertex_;
		Vertex * next_vertex_;
	};
	Graph(const Graph & graph);//���ø��ƹ��캯��
	Graph operator=(const Graph & graph);//���ø�ֵ��������
	std::map<ElementType,Vertex *> m_adjacency_table_;//ͼ���ڽӱ�
	std::vector<ElementType> m_mark_vertex_vec_;//������ȱ���ʱ�洢�ѱ���ǹ��Ķ���ֵ����

};

/**
��һ�ֹ��캯����ʽ,�����ޱߵ�����ͼ
�������: ����ĸ���Ϊvertex_number
**/
template <class ElementType>
Graph<ElementType>::Graph(int vertex_number)
{
	std::cout << "�������ж����ֵ\n";
	for (int i = 0;i < vertex_number;++i)
	{   
		ElementType element_obj;
		std::cin >> element_obj;
		Vertex * ptr_vertex = new Vertex(element_obj);//��סҪ�����������ͷŵ�
		m_adjacency_table_[element_obj] = ptr_vertex;
	}
	std::cout << "��������ͼ���\n"; 
}

/**
�ڶ��ֹ��캯����ʽ,ͨ��txt�ļ�����
�������: txt�ļ���Ϊfile_name

example:
txt�ļ��Ĳ�������:
------------------------
��������
������
a b ÿһ���ߵ���β����ֵ  
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
		std::cerr << "�ļ���ʽ����ȷ\n";
	}
	else
		std::cout << "��������ͼ���\n"; 
};

/**
�������ͼ�Ķ�����
**/
template <class ElementType>
int Graph<ElementType>::GetVertexNumbers() const 
{
	return m_adjacency_table_.size();
}

/**
�������ͼ�ı���,ʱ�临�ӶȲ��ǳ���
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
�������ͼgraph��ֵΪvertex_value�Ķ���Ķ���
**/
template<class ElementType>
int Graph<ElementType>::GetDegree(const Graph & graph,const ElementType & vertex_value)
{
	return (graph.GetAdjacentVertexNumbers(vertex_value)).size();
}


/**
�������ͼgraph��������
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
�������ͼgraph����С����
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
�������ͼgraph��ƽ������
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
�����Ի��ĸ���
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
���һ��edge_begin_vertex_value->edge_end_vertex_value�ı�
**/
template<class ElementType>
void Graph<ElementType>::AddEdge(const ElementType & edge_begin_vertex_value,const ElementType & edge_end_vertex_value)
{   
	auto iter = m_adjacency_table_.find(edge_begin_vertex_value);
	Vertex * ptr_begin_vertex = nullptr;
	Vertex * ptr_end_vertex = nullptr;
	Vertex * insert_vertex = nullptr;
	if(iter == m_adjacency_table_.end())//�����ʼ������µĽڵ�
	{  
		ptr_begin_vertex = new Vertex(edge_begin_vertex_value);//��סҪ�����������ͷŵ�
		m_adjacency_table_[edge_begin_vertex_value] = ptr_begin_vertex;
	}
	else//�����ʼ�ڵ��Ѿ�����
	{
		ptr_begin_vertex = iter->second;
	}
	insert_vertex = new Vertex(edge_end_vertex_value);//�ȴ�����Ķ���
	Vertex * tmp = ptr_begin_vertex->next_vertex_;
	ptr_begin_vertex->next_vertex_ = insert_vertex;
	insert_vertex->next_vertex_ = tmp;

	//β�������Ƿ��Ѿ�����ͼ��
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
	insert_vertex = new Vertex(edge_begin_vertex_value);//�ȴ�����Ķ���
	tmp = ptr_end_vertex->next_vertex_;
	ptr_end_vertex->next_vertex_ = insert_vertex;
	insert_vertex->next_vertex_ = tmp;
}

/**
������ȱ���ͼ�����ж���
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
