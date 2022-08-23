#pragma once 

#include <iostream>
#include "Cgi.hpp"
#include "parsing.hpp"
#include <sys/socket.h>
#include "../Includes/server.hpp"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <map>
#include <vector>

class cgi;
class server;
std::vector<std::string > extract_server_names(std::vector<std::string> text_vector,int helper);
int extract_server_port(std::vector<std::string> text_vector,int helper);
std::string extract_server_root(std::vector<std::string> text_vector,int helper);
std::vector<std::string> extract_allowed_methods(std::vector<std::string> text_vector,int helper);
std::vector<std::string> extract_server_index(std::vector<std::string> text_vector,int helper);
std::string extract_server_host(std::vector<std::string> text_vector,int helper);
std::string extract_server_upload_path(std::vector<std::string> text_vector,int helper);
std::vector<std::vector<std::string > > extract_server_errors_page(std::vector<std::string> text_vector,int helper);
std::vector<std::vector<std::string > > extract_server_redirections(std::vector<std::string> text_vector,int helper); 
long long int extract_server_max_body_size(std::vector<std::string> text_vector,int helper);
bool extract_server_autoindex(std::vector<std::string > text_vector,int helper);
std::vector<std::string> split (std::string s, std::string delimiter,char *compare);
long long int extract_location_max_body_size(std::vector<std::string> text_vector,int index);
int extract_number_of_locations(std::vector <std::string> text_vector,int helper);
std::vector<std::string> parsing_request(char* buffer);
int check_post_request(std::vector<std::string > request);
int get_request_method(std::vector<std::string > request);
std::string get_request_location(std::vector<std::string > request);
std::string get_request_vrs(std::string first_line);
std::map <std::string, std::string> get_request_headers(std::vector <std::string > full_request);
 std::string get_request_body(std::vector < std::string > full_request);
std::vector<cgi> extract_server_cgi(std::vector<std::string > text_vector,int index);
std::vector<std::string > splitv2(std::string line,std::string delim);
std::string get_request_query(std::vector<std::string > request);
std::vector <std::string > split_by_space(std::vector <std::string > text_vector);
bool isnumber(const std::string& str);
std::map <std::string,std::string > extract_server_errors_page1(std::vector<std::string > text_vector,int index,std::map<std::string,std::string> default_error_pages);
//********************** get_config_infos.cpp **************************///
 std::vector<server> fill_server(std::vector <std::string > text_vector,int nb_of_servers);
void print_parsing_infos(server myserver);
int number_of_servers(std::vector <std::string > words);
int is_binded_server(std::vector<server> ss, int i);
int is_server_inside(server srv,std::vector <server> ss );
void check_words_config_file(std::vector<std::string > text_vector);
std::map <std::string,std::string > extract_server_redirections1(std::vector<std::string > text_vector,int index);
int get_request_port(std::vector<std::string> full_request);
int    specified_methods(std::string &tmp);
