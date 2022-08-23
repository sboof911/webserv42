/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:23:12 by amaach            #+#    #+#             */
/*   Updated: 2022/08/22 21:52:39 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "request.hpp"
#include "Header.hpp"
#include "Firstline.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <cstdio>
#include "server.hpp"
#include "Response_cgi.hpp"

class   Header;
class   Response_cgi;

#define MAX_BUFFER 10000

class Response
{
private:
    Header          *_header;
    Request         _request;
    server          _Serv;
    std::string     _Body;
    std::string     _location;
    std::string     _Upload_Path;
    int             _location_index;
    int             _location_type; // 0 nothing 1 file 2 directory
    bool            _is_chanked;
    long long       _File_size;
    long long       _Bytes_Sent;
    std::ifstream   _FILE_chunk;
    std::string     _Cgi_Path;
    bool            _is_cgi;
    Response();

public:
    Response(Request &request, server &Serv);
    ~Response();
    std::string get_Response( void );
    bool        get_is_chunked( void );

public:
    //*********GETTERS*********
    Header*         get_Header();
    Request         get_Request();
    server          get_Server();
    std::string     get_root();
    std::string     get_FirstLine();
    std::string     get_Body();
    std::string     get_cgi_Path();
    std::string     get_location();
    void            set_Body(std::string str);
    void            set_is_cgi(bool l) {_is_cgi = l;}

private:
 
    void        errorsPages( int Status_code );
    int         statuscode( void ); 
    int        check_location( void );
    bool        handleredirection();
    bool        check_path( void );
    int         check_methods( void );
    int         CGI( void );

    
    //********CHECKERS*********
    int         check_GET( void );
    int         check_POST( void );
    int         check_DELETE( void );
    bool        check_CGI( void );

    //***********GET***********
    int         handle_GET_Dir( void );
    int         handle_GET_autoindex( void );
    int         cgi_GET( void );
    int         file_GET( void );
    int        file_Is_chancked( void );
    void        check_chancked( void );

    //**********DELETE*********
    int         cgi_DELETE( void );
    int         file_DELETE( void );
    int         handle_DELETE_Dir( void );
    int         DELETE_all_Folder( void );

    //***********POST**********
    int         cgi_POST( void );
    int         handle_POST_Dir( void );
    int         Upload_file( std::string upload_path );

};

std::string     StatusCode(string location, int i);
std::string     file_to_string(std::string location);
std::string     RandomWord( void );
std::vector<std::string>     ft_split(std::string s1, std::string delim);
std::string     extension(std::string str);
