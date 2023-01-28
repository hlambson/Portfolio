use std::collections::HashSet;
use std::collections::VecDeque;
use super::GraphStructs;

/// Perform a breadth-first search on Graph `graph`.
///
/// # Parameters
///
/// - `graph`: The graph to search.
/// - `root`: The starting node of the graph from which to begin searching.
/// - `target`: The target node for the search.
///
/// # Returns
///
/// If the target is found, an Optional vector is returned with the history
/// of nodes visited as its contents.
///
/// If the target is not found or there is no path from the root,
/// `None` is returned.
///
pub fn breadth_first_search(graph: &GraphStructs::Graph, root: GraphStructs::Node, target: GraphStructs::Node) -> Option<Vec<u32>> {
    let mut visited: HashSet<GraphStructs::Node> = HashSet::new();
    let mut history: Vec<u32> = Vec::new();
    let mut queue = VecDeque::new();

    visited.insert(root);
    queue.push_back(root);
    while let Some(currentnode) = queue.pop_front() {
        history.push(currentnode.value());

        // If we reach the goal, return our travel history.
        if currentnode == target {
            return Some(history);
        }

        // Check the neighboring nodes for any that we've not visited yet.
        for neighbor in currentnode.neighbors(graph) {
            if !visited.contains(&neighbor) {
                visited.insert(neighbor);
                queue.push_back(neighbor);
            }
        }
    }

    // All nodes were visited, yet the target was not found.
    None
}

// Data Structures

// #[derive(Copy, Clone, PartialEq, Eq, Hash)]
// pub struct Node(u32);

// #[derive(Copy, Clone, PartialEq, Eq, Hash)]
// pub struct Edge(u32, u32);

// #[derive(Clone)]
// pub struct Graph {
//     #[allow(dead_code)]
//     nodes: Vec<Node>,
//     edges: Vec<Edge>,
// }

// impl Graph {
//     pub fn new(nodes: Vec<Node>, edges: Vec<Edge>) -> Self {
//         Graph { nodes, edges }
//     }
// }

// impl From<u32> for Node {
//     fn from(item: u32) -> Self {
//         Node(item)
//     }
// }

// impl Node {
//     pub fn value(&self) -> u32 {
//         self.0
//     }

//     pub fn neighbors(&self, graph: &Graph) -> Vec<Node> {
//         graph
//             .edges
//             .iter()
//             .filter(|e| e.0 == self.0)
//             .map(|e| e.1.into())
//             .collect()
//     }
// }

// impl From<(u32, u32)> for Edge {
//     fn from(item: (u32, u32)) -> Self {
//         Edge(item.0, item.1)
//     }
// }
