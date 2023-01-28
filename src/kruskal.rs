use super::DisjointSetUnion;
use super::GraphStructs;
// #[derive(Debug)]
// pub struct Edge {
//     source: u32,
//     destination: u32,
//     cost: u32,
// }

// impl PartialEq for Edge {
//     fn eq(&self, other: &Self) -> bool {
//         self.source == other.source
//             && self.destination == other.destination
//             && self.cost == other.cost
//     }
// }

// impl Eq for Edge {}

// impl Edge {
//     pub fn new(source: u32, destination: u32, cost: u32) -> Self {
//         Self {
//             source,
//             destination,
//             cost,
//         }
//     }
// }

pub fn kruskal(graph: &GraphStructs::Graph, number_of_vertices: u32) -> Vec<u32> {
    let mut dsu = DisjointSetUnion::DisjointSetUnion::new(number_of_vertices as usize);
    let mut edges = graph.getEdges();
    edges.sort_unstable_by(|a, b| a.weight().cmp(&b.weight()));
    let mut total_cost: u32 = 0;
    let mut final_edges: Vec<u32> = Vec::new();
    let mut merge_count: u32 = 0;
    for edge in edges.iter() {
        if merge_count >= number_of_vertices - 1 {
            break;
        }

        let source: u32 = edge.source();
        let destination: u32 = edge.destination();
        if dsu.merge(source as usize, destination as usize) < std::usize::MAX {
            merge_count += 1;
            let cost: u32 = edge.weight();
            total_cost += cost;
            let final_edge =  destination;
            final_edges.push(final_edge);
        }
    }
    final_edges
}