import init, { test_case, create_random_graph, breadth_first_search, depth_first_search, kruskal } from "./pkg/graph_algorithms.js";

// BFS

//let arrBFS = new Array(100);
//let arrDFS = new Array(100);
//let arrKrusk = new Array(100);

//for (let x = 0; x < 100; x ++) {

//let cycleGraph = wasm.create_cycle_graph(10);

    async function run() {
        await init();
        let randomGraph = create_random_graph(1000,20); //create random graph with 100 vertices and up to 20 edges per vertex


        var startTime = performance.now();
        test_case(randomGraph, 1, 50, 1000).then(() => console.log("test case done")) //run test case with root 1, target 50
        var endTime = performance.now();
        var elapsed = endTime - startTime;

        document.getElementById("multithread").innerHTML = "Time Taken Multithread: " + elapsed + " Milliseconds";

        var startTime = performance.now();
        let bfsVec = breadth_first_search(randomGraph, 1, 50);
        let dfsVec = depth_first_search(randomGraph, 1, 50);
        let kruskVec = kruskal(randomGraph,1000);
        var endTime = performance.now();
        var elapsed = endTime - startTime;

        document.getElementById("single").innerHTML = "Time Taken Single Thread: " + elapsed + " Milliseconds";
}

run();


//let bfsVec = wasm.breadth_first_search_thread(cycleGraph, 1 ,5).then(x => console.log(x)).catch(e => console.error(e));
// document.getElementById("bfs").innerHTML = "BFS from 1 to 5: " + bfsVec;