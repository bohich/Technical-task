#include <iostream>
#include <string>
#include <thread>
#include "library/searchfile.h"
#include <fstream>
#include <stack>
#include <mutex>
#include <future>
#include <chrono>


SearchFile sf;

std::atomic_bool atom_b = 0;
std::atomic<uint_fast32_t> counter = 0;
std::mutex mux;

void do_job(std::stack<fs::path> &st, const std::string &filename)
{
    fs::path pt;
    SearchFile s;
    {
        std::lock_guard<std::mutex> lock(mux);
        pt = st.top();
        if(st.empty() == 0)
        {
            st.pop();
        }
        else
        {
            return;
        }
        
    }
    
    if(0 == fs::is_regular_file(pt))
    {   
        if(s.find_file_from_directory(filename, pt))
        {
            atom_b = 1;
            const std::string path = s.get_current_dir().string();
            std::fstream f;
            f.open(path);
            if(f.is_open())
            {
                
                f << path; 
                f.close();
                std::cout<<"Writing file success\n";
            }
            else  
            {
                std::cout<<"Open file error\n";  
            }
        }
    }
    --counter; 
}

int main()
{ 
    const std::string filename = "MyFile.txt";
    const std::string path = "/";
    std::stack<fs::path> st;

    for(auto &p: fs::directory_iterator(path))
    {
        if(0 == fs::is_regular_file(p.path()))
        {
            st.push(p.path());
        }
    }
    
    while(true && (0 == st.empty()))
    {
        if(8 <= counter) continue;
        if((1 == atom_b) || (1 == st.empty())) break;
        std::promise<void> p;
        std::future<void> f3 = p.get_future();
        std::thread(do_job, std::ref(st), std::ref(filename)).detach();
        ++counter;
    }
    
    while(true && (0 == counter));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}