#pragma once

# include "mappy_client.hpp"
# include <vector>


struct Edge
{
	int		u;
	int		v;
	int		weight;
};

struct Node
{
	int					index;
	int					is_road;
	int					nb_cars;

	int					color;
	int					weight;
	int					cost;

	std::vector<int>	adjacency_list;

	Node() = default;
	Node(int index, int is_road, int nb_cars)
	{
		this->index = index;
		this->is_road = is_road;
		this->nb_cars = nb_cars;
		this->color = 4242;
	}
};

class Graph
{
	private:
		int									_mapWidth;
		int									_mapHeight;
		int									_start;
		int									_destination;

		int									_vertexNumber;
		int									_edgeNumber;
		std::vector<std::vector<Edge> >		_graph;

	public:
		std::vector<Node>					_nodes;
		Graph();
		Graph(Map &);
		~Graph();

		void		addNode(int, int, Square &);
		void		addEdge(Edge edge);
		void		addNeighbors(Node &node, Map const & map);
		void		removeNode(Node node);
		void		removeEdge(Edge edge);

		Node&		getNode(int index);
		Edge		getEdge(int , int);

		void		print_graph() const;

		int			getMapWidth(void) const;
		int			getMapHeight(void) const;
};

// std::ostream & operator<<( std::ostream & o, Graph const & rhs);
