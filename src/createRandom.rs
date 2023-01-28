use super::GraphStructs;
use rand::Rng;

pub fn create_random_graph(v: u32, n: u32) -> GraphStructs::Graph {    let mut nodes = Vec::new();
    let mut edges = Vec::new();
    for x in 0..v {
        let node = GraphStructs::Node::from(x);
        nodes.push(node);
    }
    for i in 0..v {
        let num = rand::thread_rng().gen_range(1..n);
        for j in 1..num {
            let end = rand::thread_rng().gen_range(0..n);
            let weight = rand::thread_rng().gen_range(1..100);  
            let edge = GraphStructs::Edge::from((i as u32,end as u32, weight as u32));
            edges.push(edge);
        }
    }

    let graph = GraphStructs::Graph::new(nodes,edges);
    return graph;
}

