pub struct DSUNode {
    parent: usize,
    size: usize,
}

pub struct DisjointSetUnion {
    nodes: Vec<DSUNode>,
}

// We are using both path compression and union by size
impl DisjointSetUnion {
    // Create n+1 sets [0, n]
    pub fn new(n: usize) -> DisjointSetUnion {
        let mut nodes = Vec::new();
        nodes.reserve_exact(n + 1);
        for i in 0..=n {
            nodes.push(DSUNode { parent: i, size: 1 });
        }
        DisjointSetUnion { nodes }
    }
    pub fn find_set(&mut self, v: usize) -> usize {
        if v == self.nodes[v].parent {
            return v;
        }
        self.nodes[v].parent = self.find_set(self.nodes[v].parent);
        self.nodes[v].parent
    }
    // Returns the new component of the merged sets,
    // or std::usize::MAX if they were the same.
    pub fn merge(&mut self, u: usize, v: usize) -> usize {
        let mut a = self.find_set(u);
        let mut b = self.find_set(v);
        if a == b {
            return std::usize::MAX;
        }
        if self.nodes[a].size < self.nodes[b].size {
            std::mem::swap(&mut a, &mut b);
        }
        self.nodes[b].parent = a;
        self.nodes[a].size += self.nodes[b].size;
        a
    }
}