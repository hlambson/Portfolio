use serde::{Serialize, Deserialize};

#[derive(Copy, Clone, PartialEq, Eq, Hash, Serialize, Deserialize)]
pub struct Node(u32);

#[derive(Copy, Clone, PartialEq, Eq, Hash, Serialize, Deserialize)]
pub struct Edge(u32, u32, u32);

#[derive(Clone, Serialize, Deserialize)]
pub struct Graph {
    #[allow(dead_code)]
    nodes: Vec<Node>,
    edges: Vec<Edge>,
}

impl Graph {
    pub fn new(nodes: Vec<Node>, edges: Vec<Edge>) -> Self {
        Graph { nodes, edges }
    }
    pub fn getEdges(&self) -> Vec<Edge> {
        let mut newEdges = self.edges.to_vec();
        newEdges
    }
    pub fn getNodes(&self) -> Vec<Node> {
        let mut newNodes = self.nodes.to_vec();
        newNodes
    }
}

impl From<u32> for Node {
    fn from(item: u32) -> Self {
        Node(item)
    }
}

impl Node {
    pub fn value(&self) -> u32 {
        self.0
    }

    pub fn neighbors(&self, graph: &Graph) -> Vec<Node> {
        graph
            .edges
            .iter()
            .filter(|e| e.0 == self.0)
            .map(|e| e.1.into())
            .collect()
    }
}

impl From<(u32, u32, u32)> for Edge {
    fn from(item: (u32, u32, u32)) -> Self {
        Edge(item.0, item.1, item.2)
    }
}

impl Edge {
    pub fn source(&self) -> u32 {
        self.0
    }
    pub fn destination(&self) -> u32 {
        self.1
    }
    pub fn weight(&self) -> u32 {
        self.2
    }
}
