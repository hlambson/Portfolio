use std::collections::HashSet;
use std::collections::VecDeque;
use super::GraphStructs;

// Perform a Depth First Search Algorithm to find a element in a graph
//
// Return a Optional with a vector with history of Node visiteds
// or a None if the element not exists on the graph
pub fn depth_first_search(graph: &GraphStructs::Graph, root: GraphStructs::Node, target: GraphStructs::Node) -> Option<Vec<u32>> {
    let mut visited: HashSet<GraphStructs::Node> = HashSet::new();
    let mut history: Vec<u32> = Vec::new();
    let mut queue = VecDeque::new();
    queue.push_back(root);

    // While there is an element in the queue
    // get the first element of the Node queue
    while let Some(current_Node) = queue.pop_front() {
        // Added current Node in the history of visiteds Node
        history.push(current_Node.value());

        // Verify if this Node is the objective
        if current_Node == target {
            // Return the Optional with the history of visiteds Node
            return Some(history);
        }

        // For each over the neighbors of current Node
        for neighbor in current_Node.neighbors(graph).into_iter().rev() {
            // Insert in the HashSet of visiteds if this value not exist yet
            if visited.insert(neighbor) {
                // Add the neighbor on front of queue
                queue.push_front(neighbor);
            }
        }
    }

    // If all Node is visited and the objective is not found
    // return a Optional with None value
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
//     vertices: Vec<Node>,
//     edges: Vec<Edge>,
// }

// impl Graph {
//     pub fn new(vertices: Vec<Node>, edges: Vec<Edge>) -> Self {
//         Graph { vertices, edges }
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

//     pub fn neighbors(&self, graph: &Graph) -> VecDeque<Node> {
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
