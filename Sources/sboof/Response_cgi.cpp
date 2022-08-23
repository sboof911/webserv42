/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response_cgi.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:29:32 by amaach            #+#    #+#             */
/*   Updated: 2022/08/23 02:27:35 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/sboof/Response_cgi.hpp"
#include <cstdio>

Response_cgi::Response_cgi( void ) :    _extention(""),
                                        _cgi_path(""),
                                        _methods(std::vector<std::string>()),
                                        _envp(NULL),
                                        _argv(NULL),
                                        _cgi_response_file(""),
                                        _header(""),
                                        _FILEINLINE("") {}

Response_cgi::~Response_cgi( void )
{
    // int i = 0;
    // while (_envp[i] != NULL)
    //     free(_envp[i]);
    // free (_envp);
    // for (int i =0; i < 2; i++)
    //     free(_argv[i]);
    // free(_argv);
    _methods.clear();
    _extention.clear();
    _cgi_path.clear();
    _cgi_response_file.clear();
    _header.clear();
    _FILEINLINE.clear();
}

std::string Response_cgi::header_to_envp(std::map<std::string, std::string>::iterator it)
{
    std::string     tmp = "HTTP_";

    for(int i = 0; i != it->first.size(); i++)
        tmp.push_back(toupper(it->first[i]));
    tmp.push_back('=');
    tmp.append(it->second);
    return (tmp);
}

void    Response_cgi::set_envp(Response& response, Request &request, std::string root_path)
{
    std::vector<std::string>    envp_vect;

    envp_vect.push_back("GETAWAY_INTERFACE=CGI/1.1");
    envp_vect.push_back("SERVER_PROTOCOL=HTTP/1.1");
    envp_vect.push_back("SERVER_PORT=" + std::to_string(response.get_Server().get_listen_port()));
    envp_vect.push_back("REMOTE_ADDR=0.0.0.0");
    envp_vect.push_back("PATH_INFO=" + request.get_location());
    envp_vect.push_back("SCRIPT_FILENAME=" + root_path);
    envp_vect.push_back("QUERY_STRING=" + request.get_query());
    envp_vect.push_back("REQUEST_METHOD=" + request.get_method());
    envp_vect.push_back("REDIRECT_STATUS=true");
    envp_vect.push_back("FCGI_ROLE=RESPONDER");
    envp_vect.push_back("REQUEST_SCHEME=http");
    envp_vect.push_back("REMOTE_PORT=0");
    envp_vect.push_back("REQUEST_URI=" + request.get_location().substr(0, request.get_location().find_last_of("/")));
    envp_vect.push_back("DOCUMENT_URI=" + request.get_location() + request.get_query());
    envp_vect.push_back("SCRIPT_NAME=" +  request.get_location());
    envp_vect.push_back("PATH_TRANSLATED=" + root_path);
    envp_vect.push_back("SERVER_NAME=localhost");
    envp_vect.push_back("DOCUMENT_ROOT=" + response.get_root());
    envp_vect.push_back("REDIRECT_STATUS=200");
    envp_vect.push_back("SERVER_SOFTWARE=webserv/1.1");
    envp_vect.push_back("PATH=" + std::string(std::getenv("PATH")));
    if (request.get_headrs()["Cookie"].size() > 0)
        envp_vect.push_back("HTTP_COOKIE=" + request.get_headrs()["Cookie"]);
	if (request.get_body_len() == 0)
    {
        envp_vect.push_back("CONTENT_TYPE=text/html; charset=UTF-8");
        envp_vect.push_back("CONTENT_LENGTH=0");
    }
    else
    {
        envp_vect.push_back("CONTENT_TYPE=" + request.get_headrs()["Content-Type"]);
        envp_vect.push_back("CONTENT_LENGTH=" + to_string(request.get_body().size()));
    }
    std::map<std::string, std::string>  tmp = request.get_headrs();
    for (std::map<std::string, std::string>::iterator it = tmp.begin(); it != tmp.end(); it++)
        envp_vect.push_back(header_to_envp(it));
    _envp = (char**)malloc(sizeof(char*) * (envp_vect.size() + 1));
    size_t i = -1;
    while (++i < envp_vect.size())
        _envp[i] = strdup(envp_vect[i].c_str());
    _envp[i] = NULL;
}

void        Response_cgi::set_argv(std::string root_path)
{
    _argv = (char**)malloc(sizeof(char*) * 3);

    _argv[0]  = strdup(_cgi_path.c_str());
    _argv[1]  = strdup(root_path.c_str());
    _argv[2]  = NULL;
}

bool   Response_cgi::set_cgi_response_file()
{

    _cgi_response_file = "/var/tmp/cgi_" + RandomWord() + "_response";

    std::ofstream    file(_cgi_response_file);

    if (file.is_open() == 0)
        return false;
    return true;
}

bool    Response_cgi::init_data(Response& response)
{
    this->_cgi_path = response.get_cgi_Path();
    if (!set_cgi_response_file())
        return (false);
    return true;
}

std::string         set_file_body(Request &request)
{
    std::string     FILE = "/var/tmp/cgi_" + RandomWord() + "_body";
    std::ofstream   file(FILE);

    file << request.get_body();
    file.close();
    chmod(FILE.c_str(), 0777);
    return FILE;
}

int     Response_cgi::execute(Response& response, Request &request, std::string root_path)
{
    pid_t   pid;

    if (!init_data(response))
        return (500);
    pid = fork();
    if (pid == -1)
        return 502;
    if (pid == 0)
    {
        int cgi_response_fd = 0;
        int body_fd = 0;
        std::string     body_file;
        set_envp(response, request, root_path);
        set_argv(root_path);
        if (request.get_body_len() > 0)
            body_file = set_file_body(request);
        if ((cgi_response_fd = open(_cgi_response_file.c_str(), O_WRONLY)) < 0)
            exit(21);
        if (0 < request.get_body_len() && (body_fd = open(body_file.c_str(), O_RDONLY)) < 0)
            exit(21);
        if ((request.get_method().compare("POST") == 0) && dup2(body_fd, STDIN_FILENO) < 0)
            exit(21);
        close(body_fd);
        if (dup2(cgi_response_fd, STDOUT) < 0)
            exit(21);
        close(cgi_response_fd);
        if (execve(_cgi_path.c_str(), _argv, _envp) < 0)
        {
            std::cerr << "ERRNO = "<< errno << strerror(errno) << " " << _argv[0] << " " << _argv[1] << std::endl;
            exit(21);
        }
        exit(0);
    }
    else
    {
        int status;
        if (waitpid(pid, &status, 0) == -1)
            return 500;
        int exit_status;
        if (WIFEXITED(status) && (exit_status = WEXITSTATUS(status)) == 21)
            return 502;
        else if (WIFEXITED(status) && (exit_status = WEXITSTATUS(status)) == 204)
            return 204;
    }

    fillResponseBuffer(response);
    return 200; 
}

void        Response_cgi::set_header(Response & response)
{
    (void) response;
    std::ifstream               FILE(this->_cgi_response_file);

    // std::cout << this->_cgi_response_file << "#     ///////\n"; 
    if (FILE.is_open())
    {
        std::string                 LINE;
        size_t                      header_index;

        while (getline (FILE, LINE))
            this->_FILEINLINE += LINE + "\n";
    std::cout << "THE BODY IS = " << this->_FILEINLINE << std::endl << "FILE END\n";
        header_index = this->_FILEINLINE.find("\n\n");
        if (header_index != std::string::npos)
        {
            this->_header = this->_FILEINLINE.substr(0, header_index + 3);
            this->_FILEINLINE.erase(0, header_index + 3);
        }
        else
            this->_header = "";
    }
    FILE.close();
}

std::string Response_cgi::set_status( Response & response )
{
    std::string                 status = response.get_Request().get_version() + " 200 OK\n";
    size_t                      status_index = 0;
    size_t                      len;

    // std::cout << response.get_Request().get_version() << std::endl;
    if (_header.length())
        status_index = this->_header.find(response.get_Request().get_version());
    if (status_index != std::string::npos && !this->_header.empty())
    {
        len = this->_header.find("\n", 0);
        std::cout << "The Header = " << this->_header << "The Header end " << std::endl;
        status = _header.substr(status_index + response.get_Request().get_version().size(), len);
        std::cout << "I M IN \n";
    }
    return status;
}

void        Response_cgi::fillResponseBuffer( Response & response )
{
    set_header(response);
    std::string     tmp("");

    tmp = set_status(response);
    tmp += "Content-Lenght:" + to_string(this->_FILEINLINE.size()) + "\n";
    tmp += this->_header;
    // std::cout << "THE HEADER = " << tmp << std::endl;
    // std::cout << "THE HEADER IS = " << this->_header << std::endl << "HEADER END\n";
    tmp += this->_FILEINLINE;
    response.set_Body(tmp);
    response.set_is_cgi(true);
    // std::cout << "THE BODY IS = " << this->_FILEINLINE << std::endl << "FILE END\n";
    std::cout << "THE RESPONSE = " << response.get_Body() << std::endl;
    // std::cout << "THE FILE = " << this->_FILEINLINE << std::endl;
    // remove(_cgi_response_file.c_str());
}