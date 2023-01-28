use std::{
    slice,
    fs,
    io::{prelude::*, BufReader},
    net::{TcpListener, TcpStream},
    time::SystemTime,
};

use graph_algorithms::ThreadPool;


fn main() {
    let listener = TcpListener::bind("127.0.0.1:7878").unwrap(); //listen on this address and port
    let pool = ThreadPool::new(6); //create thread pool to execute jobs

    for stream in listener.incoming() { //loop and check incoming messages
        let stream = stream.unwrap();
        
        pool.execute(|| { //execute the job that comes in
            let start = SystemTime::now();
            handle_connection(stream);
            let time = match start.elapsed() {  
                Ok(elapsed) => {
                    elapsed.as_millis() as usize
                },
                Err(_) => {
                    panic!("Error on serving files");
                }
            };
            println!("Time taken to serve files in milliseconds: {}",time);
        });
    }

}

fn handle_connection(mut stream: TcpStream) {
    let buf_reader = BufReader::new(&mut stream); // copy of the stream
    let request_line = buf_reader.lines().next().unwrap().unwrap(); // get the next header
    
    let (status_line, filename) = match &request_line[..] { //check what request came through and redirect to correct page
        "GET / HTTP/1.1" => ("HTTP/1.1 200 OK", "threadTest.html"),
        "GET /bfs HTTP/1.1" => ("HTTP/1.1 200 OK", "bfs.html"),
        "GET /dfs HTTP/1.1" => ("HTTP/1.1 200 OK", "dfs.html"),
        "GET /kruskal HTTP/1.1" => ("HTTP/1.1 200 OK", "kruskal.html"),
        "GET /pkg/graph_algorithms.js HTTP/1.1" => {
            ("HTTP/1.1 200 OK", "pkg/graph_algorithms.js")
        },
        "GET /pkg/graph_algorithms_bg.wasm HTTP/1.1" => ("HTTP/1.1 200 OK", "pkg/graph_algorithms_bg.wasm"),
        _ => ("HTTP/1.1 404 NOT FOUND", "404.html"),
    };

//write out to browser
    //wasm needs to be sent as not utf-8
    if filename == "pkg/graph_algorithms_bg.wasm" {
        let mut contents = fs::read(filename).unwrap();
        let length = contents.len();
        let response =  format!(
            "{status_line}\r\nContent-Length: {length}\r\n\r\n"
        );
        let mut bytes = response.as_bytes().to_vec();
        bytes.append(&mut contents);

        let bytes: &[u8] = unsafe {
            slice::from_raw_parts(
            bytes.as_ptr() as *const u8,
            bytes.len()
            )
        };

    stream.write_all(bytes).unwrap()
  }

  //send everything else as utf-8
  else {
   
    let contents = fs::read_to_string(filename).unwrap();
    let length = contents.len();
    let response =
        format!("{status_line}\r\nContent-Length: {length}\r\n\r\n{contents}");

    stream.write_all(response.as_bytes()).unwrap();
  }
}

