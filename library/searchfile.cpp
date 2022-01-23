#include "searchfile.h"


void SearchFile::show_current_dir()
{
    std::cout<< curr_path <<"\n";
}

void SearchFile::show_directory_list()
{
    for(auto& p: fs::directory_iterator(curr_path))
        if(p.is_regular_file())
            std::cout << p.path() <<" (file)" << '\n';
        else
            std::cout << p.path() << "\n";
}

void SearchFile::show_directory_list(const fs::path &path)
{
    if(fs::is_directory(path))
        for(auto& p: fs::directory_iterator(path))
            if(p.is_regular_file())
                std::cout << p.path() <<" (file)" << '\n';
            else
                std::cout << p.path() << "\n";
    else
        std::cout<<"Entered path is not a directory\n";
}

bool SearchFile::find_file_by_name(const std::string &file_name)
{
    fs::path path(curr_path);
    path /= file_name;
    if(fs::exists(path))
    {
        return true;
    }
    else  
    {
    std::cout<<"File not exists\n";
    return false;
    }
}

void SearchFile::enter_directory(const std::string &directory_name)
{
    fs::path p = curr_path;
    p /= directory_name;
    if(fs::is_directory(p))
        set_current_dir(p);
    else
        std::cout<<"Entered path is not a directory\n";
        return;
}


void SearchFile::set_current_dir(const fs::path &path)
{
    curr_path = path;
}


void SearchFile::move_to_previous_directory()
{
    curr_path = curr_path.parent_path();
}

bool SearchFile::find_file_from_directory(const std::string &file_name, const fs::path &path)
{
    if(fs::is_directory(path))  
    { 
        fs::path pt = path;
        for(auto& p: fs::recursive_directory_iterator(pt, fs::directory_options::skip_permission_denied))
        {
            pt = p;
            if(pt.filename()==file_name)
            {
                set_current_dir(pt);
                return true;
            }
            else  
            {
                //uncomment this line to see how the function search file
                //std::cout<<path<<"\n";
                continue;
            }
        }
    }
    else
    {
        std::cout<<"Entered path is not a directory\n"; 
        return false;
    }
    std::cout<<"File doesn`t exist\n";
    return false;
}

bool SearchFile::find_file_in_directory(const std::string &file_name, const fs::path &path)
{
    if(fs::is_directory(path))
    {
        fs::path p = path;
        p /= file_name;
        if(fs::exists(p))
        {
            set_current_dir(p);
            return true;
        }
    }
    else
    {
        std::cout<<"Entered path is not a directory\n";
        return false;
    }
    std::cout<<"File doesn`t exist\n";
    return false;
}

uint_fast32_t SearchFile::get_num_of_files_recursively(const fs::path &path)
{
    uint_fast32_t num = 0;
    if(fs::is_directory(path))  
    { 
        for(fs::recursive_directory_iterator it(path,fs::directory_options::skip_permission_denied); it != fs::recursive_directory_iterator(); ++it)
        {
            ++num;
        } 
    }
    else
    {
        std::cout<<"Entered path is not a directory\n";
        return 0;
    }
    return num;
}


uint_fast32_t SearchFile::get_num_of_files_in_directory(const fs::path &path)
{
    uint_fast32_t num = 0;
    if(fs::is_directory(path)) 
    {
        for(auto& p: fs::directory_iterator(path)) 
        {
            ++num;
        }
    }
    else
    {
        std::cout<<"Entered path is not a directory\n";
        return 0;
    }
    return num;
}

fs::path SearchFile::get_current_dir()
{
    return curr_path;
}