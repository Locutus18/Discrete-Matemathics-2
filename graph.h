#ifndef __GRAPH_H__
#define __GRAPH_H__

#include<vector>
#include<map>

enum Graph_T {
	PETERSEN,
};

template<typename Node,typename Weight, bool Directed>
class Graph
{
private:
	//Súlyok szomszédsági
	typedef std::vector<Weight> Row; // sor
	typedef std::vector<Row> Edges; // mátrix, teljes gráf
	typedef typename Row::size_type size_type;
	typedef typename Row::iterator iterator;
	//Bool szomszédsági
	typedef std::vector<bool> L_Row;
	typedef std::vector<L_Row> L_Edges;
	typedef typename L_Row::size_type l_size_type;
	typedef typename L_Row::iterator l_iterator;
	//Illeszkedesi Matrix
	typedef std::vector<int> I_Row;
	typedef std::vector<I_Row> I_Edges;
	typedef typename I_Row::size_type i_size_type;
	typedef typename I_Row::iterator i_iterator;
	
	typedef std::map<Node,size_type> NodeCont;
	typedef typename NodeCont::iterator node_iterator;
	typedef typename NodeCont::const_iterator node_c_iterator;
	Edges edges;
	L_Edges l_edges;
	NodeCont nodes;
public:
	
	Graph() {}
	Graph(Graph_T t) {
		switch(t) {
		case PETERSEN:
			
			break;
		}
	}
	
	void add( const Node& n )
	{
		if( !nodes.count(n) ) 
		{
			nodes[n] = nodes.size() - 1;
			for(size_type i = 0; i < edges.size(); ++i) 
			{
				l_edges[i].push_back(false);
				edges[i].push_back(Weight());
			}
			l_edges.push_back( L_Row( nodes.size(), false ) );
			edges.push_back( Row( nodes.size(), Weight() ) );
		}
	}
	void add( const Node& r, const Node& c, const Weight &k )
	{
		node_c_iterator rit = nodes.find(r),
			cit = nodes.find(c);
		if( rit != nodes.end() && cit != nodes.end() )
		{
			size_type rnum = rit->second,
				cnum = cit->second;
			edges[rnum][cnum] = k;
			l_edges[rnum][cnum] = true;
			if( !Directed )
			{
				edges[cnum][rnum] = k;
				l_edges[cnum][rnum] = true;
			}
		}
	}
	void print() 
	{
		for(node_c_iterator rit = nodes.begin(); rit != nodes.end(); rit++)
		{
			std::cout << rit->first << " " << rit->second << std::endl;
		}
		std::cout << std::endl;
		for(size_type i = 0; i < edges.size(); ++i)
		{
			for(size_type j = 0; j < edges[i].size(); ++j)
			{
				std::cout << edges[i][j] << " ";
			}
			std::cout << std::endl;	
		}
		std::cout << std::endl;
		for(size_type i = 0; i < l_edges.size(); ++i)
		{
			for(size_type j = 0; j < l_edges[i].size(); ++j)
			{
				std::cout << l_edges[i][j] << " ";
			}
			std::cout << std::endl;	
		}	
	}
	void remove( const Node& r, const Node& c )
	{
		node_c_iterator rit = nodes.find(r),
			cit = nodes.find(c);
		if( rit != nodes.end() && cit != nodes.end() )
		{
			size_type rnum = rit->second,
				cnum = cit->second;
			l_edges[rnum][cnum] = false;
			edges[rnum][cnum] = Weight();
			if( !Directed )
			{
				edges[cnum][rnum] = Weight();
				l_edges[cnum][rnum] = false;
			}
		}
	}
	bool is_directed() const
	{
		return Directed;
	}
	Weight has(const Node& r , const Node& c) const
    {
        node_c_iterator rit = nodes.find(r),
                    cit = nodes.find(c);
        if ( rit != nodes.end() && cit != nodes.end() )
        {
            size_type rnum = rit->second,
                        cnum = cit->second;
						
            return edges[rnum][cnum];
        }
        return 0;
    }
	size_type countNodes() const
    {
        return nodes.size();
    }
	size_type countEdges() const
    {
        l_size_type res = 0;
        for( l_size_type i = 0; i < l_edges.size() ; ++i )
        {
            for( l_size_type j = 0; j < l_edges[i].size() ; ++j )
            {
				res += l_edges[i][j];
            }
        }
        return Directed ? res : res / 2;
    }
	void remove( const Node& n )
    {
        node_iterator it = nodes.find( n );
        if( it != nodes.end() )
        {
            size_type x = it->second;
            edges.erase( edges.begin() + x );
            for( size_type i = 0; i < edges.size() ; ++i )
            {
                edges[i].erase( edges[i].begin() + x );
            }
            nodes.erase( it );
            for( it = nodes.begin() ; it != nodes.end() ; ++it )
            {
                if( it->second > x )
                {
                    --it->second;
                }
            }
        }
    }
};



#endif
