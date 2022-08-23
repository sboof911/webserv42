/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Firstline.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:14:43 by amaach            #+#    #+#             */
/*   Updated: 2022/08/22 17:22:35 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/sboof/Firstline.hpp"

FirstLine::FirstLine(Request& request) : _req(request)
{
    this->_StatusCode[200] = "OK";
	this->_StatusCode[201] = "Created";
	this->_StatusCode[202] = "Accepted";
	this->_StatusCode[204] = "No Content";                  //
	this->_StatusCode[300] = "Redirection";                 //
	this->_StatusCode[301] = "Moved Permanently";                   //
	this->_StatusCode[302] = "Found";                   //
	this->_StatusCode[400] = "Bad Request";                 //
	this->_StatusCode[401] = "Unauthorized";                    //              <--- this is for quick search instead of lots of ifs and elses
	this->_StatusCode[403] = "Forbidden";                   //
	this->_StatusCode[404] = "Not Found";                   //
	this->_StatusCode[405] = "Method Not Allowed";                  //
	this->_StatusCode[408] = "Request Timeout";                 //
	this->_StatusCode[413] = "Payload Too Large";                   //
	this->_StatusCode[414] = "URI Too Long";
	this->_StatusCode[500] = "Internal Server Error";
	this->_StatusCode[501] = "Not Implemented";
	this->_StatusCode[502] = "Bad Gateway";
	this->_StatusCode[503] = "Service Unavailable";
	this->_StatusCode[505] = "HTTP Version Not Supported";
}

FirstLine::~FirstLine()
{
	this->_StatusCode.clear();
}

std::string     FirstLine::First_Line(int Key)
{
    return (std::string(this->_req.get_version() + " " + std::to_string(Key) + std::string(" ") + this->_StatusCode[Key] + "\r\n"));
}