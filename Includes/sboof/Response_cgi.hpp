/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response_cgi.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 22:39:39 by amaach            #+#    #+#             */
/*   Updated: 2022/08/22 20:01:49 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef CGI_
# define CGI_

#include "Response.hpp"

#define STDOUT 1

class   Response;
class   Request;

class Response_cgi
{
    private:
        std::string                     _extention;
        std::string                     _cgi_path;
        std::vector<std::string>        _methods;
        char**                          _envp;
        char**                          _argv;
        std::string                     _cgi_response_file;
        std::string                     _header;
        std::string                     _FILEINLINE;
    
    public:
        Response_cgi();
        ~Response_cgi();
        int     execute(Response& response, Request &request, std::string root_path);

    private:
        void            set_envp(Response& response, Request &request, std::string root_path);
        void            set_argv(std::string root_path);
        std::string     header_to_envp(std::map<std::string, std::string>::iterator it);

        bool            set_cgi_path( void );
        bool            set_cgi_response_file();
        bool            init_data(Response& response);

        void            fillResponseBuffer( Response & response );
        void            set_header( Response & response );
        std::string     set_status( Response & response );
};

#endif