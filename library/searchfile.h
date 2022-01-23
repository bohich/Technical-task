#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <stdint.h>
namespace fs = std::filesystem;
class SearchFile
{
private:
    fs::path curr_path = "/";
public:
    SearchFile(){}
    SearchFile(const fs::path path):curr_path(path){}

    /*THIS IS A WORKING FUNCTION TO FIND FILE USING ONE(!) THREAD
    search file by name in system, starting from directory, represented by "path". Returns '1' if
    file with name "file_name" exists, and 0 if not.*/
    bool find_file_from_directory(const std::string &file_name, const fs::path &path = "/");

    //will change current path to "path"
    void set_current_dir(const fs::path &path);
    
    //prints path of current directory
    void show_current_dir();
    
    //prints files and folders in current directory
    void show_directory_list();

    //prints files and folders in "path" directory
    void show_directory_list(const fs::path &path);

    /*will change current path, for ex. "/home" will change to "/home/videos, 
    if directory_name = "videos"*/
    void enter_directory(const std::string &directory_name);


    /*search file by name in directory, represented by "path". Returns '1' if
    file with name "file_name" exists, and 0 if not.*/
    bool find_file_in_directory(const std::string &file_name, const fs::path &path = "/");

    /*search file by name in CURRENT directory, represented by "path". Returns '1' if
    file with name "file_name" exists, and 0 if not.*/
    bool find_file_by_name(const std::string &file_name);
    
    /*will change current path, for ex. "//home/videos" will change to "/home", 
    if directory_name = "videos"*/
    void move_to_previous_directory();

    //returns number of existing files on system, starting from "path" directory
    uint_fast32_t get_num_of_files_recursively(const fs::path &path = "/");

    //returns number of existing files in "path" directory
    uint_fast32_t get_num_of_files_in_directory(const fs::path &path);

    //returns current path
    fs::path get_current_dir();
};