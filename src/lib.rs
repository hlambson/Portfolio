mod utils;
pub mod bfs;
pub mod dfs;
pub mod DisjointSetUnion;
pub mod kruskal;
pub mod GraphStructs;
pub mod createCycle;
pub mod createRandom; 

use wasm_bindgen::prelude::*;
use rand::Rng;
use wasm_mt::prelude::*;
use wasm_mt::utils::console_ln;

use std::{
    sync::{mpsc, Arc, Mutex},
    thread,
};


// When the `wee_alloc` feature is enabled, use `wee_alloc` as the global
// allocator.
#[cfg(feature = "wee_alloc")]
#[global_allocator]
static ALLOC: wee_alloc::WeeAlloc = wee_alloc::WeeAlloc::INIT;

#[wasm_bindgen]
extern {
    fn alert(s: &str);
}

// Create Cycle Graph with v vertices 
#[wasm_bindgen]
pub fn create_cycle_graph(v:u32) -> JsValue {
   let graph = createCycle::create_cycle_graph(v);
   serde_wasm_bindgen::to_value(&graph).unwrap()
}

#[wasm_bindgen]
pub async fn create_cycle_graph_thread(v:u32) -> Result<JsValue, JsValue> {
    let pkg_js = "./pkg/graph_algorithms.js"; // path to `wasm-bindgen`'s JS binding
    let mt = WasmMt::new(pkg_js).and_init().await.unwrap();
    let th = mt.thread().and_init().await.unwrap();

    let result = exec!(&th, move || {
        let graph = createCycle::create_cycle_graph(v);
        let converted = serde_wasm_bindgen::to_value(&graph).unwrap();
        Ok(converted)
    }).await?;
    
     Ok(result)
}

// Create random graph with v vertices and up to n number of edges between vertices (random for each vertex)
#[wasm_bindgen]
pub fn create_random_graph(v:u32, n:u32) -> JsValue {
   let graph = createRandom::create_random_graph(v,n);
   serde_wasm_bindgen::to_value(&graph).unwrap()
}

#[wasm_bindgen]
pub async fn create_random_graph_thread(v:u32, n:u32) -> Result<JsValue, JsValue> {
    let pkg_js = "./pkg/graph_algorithms.js"; // path to `wasm-bindgen`'s JS binding
    let mt = WasmMt::new(pkg_js).and_init().await.unwrap();
    let th = mt.thread().and_init().await.unwrap();

    let result = exec!(&th, move || {
        let graph = createRandom::create_random_graph(v,n);
        let converted = serde_wasm_bindgen::to_value(&graph).unwrap();
        Ok(converted)
    }).await?;
    
    Ok(result)
}

// BFS
#[wasm_bindgen]
pub fn breadth_first_search(graph:JsValue, root:u32, target:u32) -> Vec<u32> {
    let graph = serde_wasm_bindgen::from_value(graph).unwrap();
    let root = GraphStructs::Node::from(root);
    let target = GraphStructs::Node::from(target);
    let mut result = bfs::breadth_first_search(&graph, root, target);
    if result != None {
        let resultCopy = result.unwrap();
        return resultCopy;
    }
    else {
        let empty = Vec::new();
        return empty;
    }
}

#[wasm_bindgen]
pub async fn breadth_first_search_thread(graph:JsValue, root:u32, target:u32) -> Result<JsValue, JsValue> {
    let pkg_js = "./pkg/graph_algorithms.js"; // path to `wasm-bindgen`'s JS binding
    let mt = WasmMt::new(pkg_js).and_init().await.unwrap();
    let th = mt.thread().and_init().await.unwrap();
    
    let graph = serde_wasm_bindgen::from_value(graph).unwrap();
    let root = GraphStructs::Node::from(root);
    let target = GraphStructs::Node::from(target);

    let result = exec!(&th, move || {
        let ans = bfs::breadth_first_search(&graph, root, target);
        if ans != None {
            let resultCopy = ans.unwrap();
            let converted = serde_wasm_bindgen::to_value(&resultCopy).unwrap();
            Ok(converted)
        }
        else {
            let empty: Vec<u32> = Vec::new();
            let converted = serde_wasm_bindgen::to_value(&empty).unwrap();
            Err(converted)
        }
       
    }).await?;

    Ok(result)
}


// DFS
#[wasm_bindgen]
pub fn depth_first_search(graph:JsValue, root:u32, target:u32) -> Vec<u32> {
    let graph = serde_wasm_bindgen::from_value(graph).unwrap();
    let root = GraphStructs::Node::from(root);
    let target = GraphStructs::Node::from(target);
    let mut result = dfs::depth_first_search(&graph, root, target);
    if result != None {
        let resultCopy = result.unwrap();
        return resultCopy;
    }
    else {
        let empty = Vec::new();
        return empty;
    }
}

#[wasm_bindgen]
pub async fn depth_first_search_thread(graph:JsValue, root:u32, target:u32) -> Result<JsValue, JsValue> {
    let pkg_js = "./pkg/graph_algorithms.js"; // path to `wasm-bindgen`'s JS binding
    let mt = WasmMt::new(pkg_js).and_init().await.unwrap();
    let th = mt.thread().and_init().await.unwrap();
    
    let graph = serde_wasm_bindgen::from_value(graph).unwrap();
    let root = GraphStructs::Node::from(root);
    let target = GraphStructs::Node::from(target);

    let result = exec!(&th, move || {
        let ans = dfs::depth_first_search(&graph, root, target);
        if ans != None {
            let resultCopy = ans.unwrap();
            let converted = serde_wasm_bindgen::to_value(&resultCopy).unwrap();
            Ok(converted)
        }
        else {
            let empty: Vec<u32> = Vec::new();
            let converted = serde_wasm_bindgen::to_value(&empty).unwrap();
            Ok(converted)
        }
       
    }).await?;

    Ok(result)
}

// Kruskal
#[wasm_bindgen]
pub fn kruskal(graph:JsValue, v:u32) -> Vec<u32> {
    let graph = serde_wasm_bindgen::from_value(graph).unwrap();
    kruskal::kruskal(&graph, v)
}

#[wasm_bindgen]
pub async fn kruskal_thread(graph:JsValue, v:u32) -> Result<JsValue, JsValue> {
    let pkg_js = "./pkg/graph_algorithms.js"; // path to `wasm-bindgen`'s JS binding
    let mt = WasmMt::new(pkg_js).and_init().await.unwrap();
    let th = mt.thread().and_init().await.unwrap();

    let graph = serde_wasm_bindgen::from_value(graph).unwrap();
    let result = exec!(&th, move || {
        let ans = kruskal::kruskal(&graph, v);
        let converted = serde_wasm_bindgen::to_value(&ans).unwrap();
        Ok(converted)
    }).await?;
    
    Ok(result)
}


pub struct ThreadPool {
    workers: Vec<Worker>,
    sender: mpsc::Sender<Job>,
}

type Job = Box<dyn FnOnce() + Send + 'static>;

impl ThreadPool {
    pub fn new(size: usize) -> ThreadPool {
        assert!(size > 0); // make sure there are workers

        let (sender, receiver) = mpsc::channel();

        let receiver = Arc::new(Mutex::new(receiver));

        let mut workers = Vec::with_capacity(size);

        for id in 0..size {
            workers.push(Worker::new(id, Arc::clone(&receiver))); //give each worker an instance of the reciever
        }

        ThreadPool { workers, sender }
    }
    pub fn execute<F>(&self, f: F)
    where
        F: FnOnce() + Send + 'static,
    {
        let job = Box::new(f);

        self.sender.send(job).unwrap();
    }
}

struct Worker {
    id: usize,
    thread: thread::JoinHandle<()>,
}

impl Worker {
    fn new(id: usize, receiver: Arc<Mutex<mpsc::Receiver<Job>>>) -> Worker {
        let thread = thread::spawn(move || loop {
            let job = receiver.lock().unwrap().recv().unwrap(); //lock mutex and grab next job

            println!("Worker {id} got a job; executing.");

            job();
        });

        Worker { id, thread }
    }
}