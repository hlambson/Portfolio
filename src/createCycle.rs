use super::GraphStructs;

pub fn create_cycle_graph(v: u32) -> GraphStructs::Graph {
    let mut nodes = Vec::new();
    let mut edges = Vec::new();
    for x in 0..v {
        let node = GraphStructs::Node::from(x);
        nodes.push(node);
        if (x == v - 1) {
            let edge = GraphStructs::Edge::from((x, 1, 0));
            let edge2 = GraphStructs::Edge::from((1,x, 0));
            edges.push(edge);
            edges.push(edge2);
        }
        else {
            let edge = GraphStructs::Edge::from((x, x + 1, 0));
            let edge2 = GraphStructs::Edge::from((x + 1,x, 0));
            edges.push(edge);
            edges.push(edge2);
        }
    }
    let cycle = GraphStructs::Graph::new(nodes, edges);
    return cycle;
}