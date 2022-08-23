/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:23:20 by amaach            #+#    #+#             */
/*   Updated: 2022/08/23 03:49:55 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/sboof/Response.hpp"



//********************************************OUTILS*********************************************//

std::vector<std::string>     ft_split(std::string s1, std::string delim)
{
    std::vector<std::string>     vector;
    std::size_t found = s1.find(delim, 1);
    std::size_t help = 0;

    while (found != std::string::npos)
    {
        if (s1.substr(help, found - help) != "/")
            vector.push_back(s1.substr(help, found - help));
        help = found;
        (delim != "/") ? help++ : help;
        found = s1.find(delim, help + 1);
    }
    vector.push_back(s1.substr(help, s1.size()));

    return (vector);
}

int     return_loc(std::vector<std::string> vec1, std::vector<std::string> vec2)
{
    std::vector<std::string> tmp1 = vec1;
    std::vector<std::string> tmp2 = vec2;
    std::vector<string>::iterator it2 = tmp2.begin();
    int     compt = 0;

    for(std::vector<string>::iterator it = tmp1.begin(); it != tmp1.end(); it++)
    {
        if (it2 != tmp2.end())
        {
            if (*it == *it2)
                compt++;
            else
                return (compt);
        }
        else
            return (0);
        it2++;
    }

    return (compt);
}

std::string     skip_slash( std::string str)
{
    std::vector<std::string> vector = ft_split(str, "/");
    std::string tmp;

    for(std::vector<std::string>::iterator it = vector.begin(); it != vector.end(); it++)
        tmp += *it;
    return (tmp);
}

std::string     extension(std::string str)
{
    std::vector<std::string>  vector;

    vector = ft_split(str, ".");

    return (vector.back());
}

std::string     file_to_string(std::string location)
{
    std::string buffer;

    std::ifstream fin(location.c_str());
    getline(fin, buffer, char(-1));
    fin.close();

    return buffer;
}

void     Response::errorsPages( int Status_Code)
{
    if (Status_Code != 200)
    {
        std::string tmp = this->_Serv.get_error_pages()[to_string(Status_Code)];
        this->_header->setHeader("Content-Type", (extension(tmp)));
        if (Status_Code == 201)
            this->_Body = "<div class=\"error\"> <div class=\"error__title\">201</div> <div class=\"error__subtitle\">Created</div> <div class=\"error__description\">" + this->_Upload_Path + " </div> </div>" + file_to_string(tmp);
        else
            this->_Body = file_to_string(tmp);
        // std::cout << " TMP " << tmp << std::endl;

        this->_header->setHeader("Content-Length", to_string(this->_Body.size()));
    }
}

std::string RandomWord( void )
{
    std::string StrWord;

    srand (time(NULL));
    int len = rand () % 10 + 1;

    for (int i = 0; i < len; i++)
        StrWord.push_back('a' + (rand () % 26));

    return StrWord;
}

//*******************************************GETTERS********************************************//

Header*     Response::get_Header()
{
    return (this->_header);
}

Request     Response::get_Request()
{
    return (this->_request);
}

server      Response::get_Server()
{
    return (this->_Serv);
}

std::string     Response::get_root( void )
{
    return (this->_location);
}

std::string     Response::get_Body( void )
{
    return (this->_Body);
}

std::string     Response::get_cgi_Path( void )
{
    return this->_Cgi_Path;
}

std::string     Response::get_location( void )
{
    return this->_location;
}

void            Response::set_Body(std::string str)
{
    this->_Body = str;
}

//***************************************MEMBER FUNCTIONS***************************************//

Response::Response(Request &request, server &Serv)
{
    this->_header = new Header(Serv, request);
    this->_request = request;
    this->_Serv = Serv;
    this->_Body = "";
    this->_location = "";
    this->_Upload_Path = "";
    this->_location_index = -404;
    this->_location_type = -404;
    this->_File_size = 0;
    this->_Bytes_Sent = 0;
    this->_Cgi_Path = "";
    this->_is_cgi = false;
}

Response::~Response()
{
    delete this->_header;
    this->_Body.clear();
    this->_location.clear();
    this->_Upload_Path.clear();
    this->_location_index = -404;
    this->_location_type = -404;
    this->_File_size = 0;
    this->_Bytes_Sent = 0;
    this->_Cgi_Path.clear();
    this->_is_cgi = false;
}

//********************************************CHECKS********************************************//

bool    Response::check_path()
{
    struct stat s;

    if (this->_request.get_method() == "POST")
        return (true);
    if( stat(this->_location.c_str(), &s) == 0 )
    {
        if( s.st_mode & S_IFDIR )
            this->_location_type = 2;
        else if( s.st_mode & S_IFREG )
            this->_location_type = 1;
        else
        {
            this->_location_type = 0;
            return (false);
        }
        return (true);
    }
    return (false);
}

bool    Response::handleredirection()
{
    int i = 0;
    std::map<std::string, std::string>  tmp = this->_Serv.get_redirections();

    for(std::map<std::string, std::string>::iterator it = tmp.begin(); it != tmp.end(); it++)
    {
        if(this->_request.get_location() == it->first)
        {
            this->_header->setHeader("Location", it->second);
            return(true);
        }
        i++;
    }
    return false;   
}

int    Response::check_location()
{
    int pos = 0;
    std::string loc;
    std::vector<std::string> help = ft_split(this->_request.get_location(), "/");
    std::vector<location> tmp = this->_Serv.get_location();
    int tmp1 = 0;

    if (this->handleredirection())
        return(2);
    for (std::vector<location>::iterator  it = tmp.begin(); it != tmp.end(); it++)
    {
        int tmp = return_loc(help, ft_split(it->get_locations_path(), "/"));
        if (pos < tmp)
        {
            pos = tmp;
            loc = it->get_root();
            loc = skip_slash(loc);
            this->_location_index = tmp1;
        }
        tmp1++;
    }
    if (pos == 0)
    {
        loc = this->_Serv.get_root();
        this->_location_index = -1;
    }
    for (std::vector<std::string>::iterator it = help.begin() + pos; it != help.end(); it++)
        loc += *it;
    this->_location = loc;
    this->_location = skip_slash(this->_location);
    return (check_path());
}

//**********************************************CGI**********************************************//

bool    Response::check_CGI( void )
{
    std::vector<std::string>   str = ft_split(this->_request.get_location(), ".");

    for (int i = 0; i < this->_Serv.get_cgi_size(); i++)
    {
        if (this->_Serv.get_cgi(i).get_cgi_name() == "." + str.back())
        {
            this->_Cgi_Path = this->_Serv.get_cgi(i).get_cgi_path();
            return (true);
        }
    }
    return (false);
}

int     Response::CGI( void )
{

    Response_cgi    cgi;

    return (cgi.execute(*this, this->_request, this->_location));
}

//**********************************************GET**********************************************//

std::string     autoindex_generator( std::string path, std::string req_loc)
{
    std::string str;
    DIR *dr;
    struct dirent *e;

    dr = opendir(path.c_str());
    str = "<html>\n<head>\n<body>\n<table>\n";

        while((e = readdir(dr)) != false)
        {
            if(e->d_name != std::string(".") && e->d_name != std::string(".."))
            {
                str += std::string("<br>") ;
                str += std::string("<a href=\"") + req_loc  + e->d_name + std::string("\">")+ e->d_name + string("</a>");    
            }
        }   
    str += "</table>\n</body>\n</head>\n</html>\n";
    closedir(dr);

   return (str);
}

int     Response::handle_GET_autoindex( void )
{
    bool tmp;

    if (this->_location_index == -1)
        tmp = this->_Serv.get_autoindex();
    else
        tmp = this->_Serv.get_location(this->_location_index).get_autoindex();
    if (tmp)
    {
        this->_header->setHeader("Content-Type", "Text/html");
        this->_Body = autoindex_generator(this->_location, this->_request.get_location());
        this->_header->setHeader("Content-Length", to_string(this->_Body.size()));
        return (200);
    }
    else
        return (403);
}

std::string    handle_index( std::vector<std::string> vector, std::string root)
{
    std::string     tmp;
    std::vector<std::string> tmp1 = vector;

    for(std::vector<std::string>::iterator it = tmp1.begin(); it != tmp1.end(); it++)
    {
        tmp = root + *it;
        if (open(tmp.c_str(), O_RDONLY) != -1)
            return (tmp);
    }
    return ("");
}

int     Response::file_GET( void )
{
    std::string     tmp;

    if (this->_location_type == 1)
        tmp = this->_location;
    else if (this->_location_type == 2)
      tmp = handle_index(this->_Serv.get_index(), this->_location);
    if (tmp.empty())
        return 404;
    if (StatusCode(extension(tmp), 1).empty())
        return 400;
    this->_header->setHeader("Content-Type", (StatusCode(extension(tmp), 1)));
    this->_Body = file_to_string(tmp);
    this->_header->setHeader("Content-Length", to_string(this->_Body.size()));
    return (200);
}

int     Response::cgi_GET( void )
{
    if (check_CGI())
        return (CGI());
    else
        return (file_GET());
}

int     Response::handle_GET_Dir( void )
{
    std::vector<std::string> tmp;

    if (this->_location_index == -1)
        tmp = this->_Serv.get_index();
    else
        tmp = this->_Serv.get_location(this->_location_index).get_index();
    if (tmp.size() > 0)
        return (cgi_GET());
    else
        return (handle_GET_autoindex());

}

int     Response::check_GET( void )
{
    if (this->_location_type == 1)
        return (cgi_GET());
    else
    {
        if (this->_location[this->_location.size() - 1] != '/')
        {
            this->_header->setHeader("Location", this->_location + "/");
            return (301);
        }
        else
            return (handle_GET_Dir());
    }
}

//**********************************************POST**********************************************//

int     Response::cgi_POST( void )
{
    if (check_CGI())
        return (CGI());
    else
        return (403);
}

int     Response::handle_POST_Dir( void )
{
    bool tmp;

    tmp = (this->_location_index == -1) ? this->_Serv.get_autoindex() : this->_Serv.get_location(this->_location_index).get_autoindex();
    if (tmp)
        return (cgi_POST());
    else
        return (403);
}

int     Response::Upload_file( std::string upload_path )
{
    this->_Upload_Path = upload_path + RandomWord() + "_Upload";
    if (this->_request.get_headrs()["Content-Type"].size() > 0)
    {
        if (StatusCode(this->_request.get_headrs()["Content-Type"], 2).empty())
            return (400);
        this->_Upload_Path += "." + StatusCode(this->_request.get_headrs()["Content-Type"], 2);
    }
    ofstream    FILE(this->_Upload_Path);
    FILE << this->_request.get_body();
    FILE.close();
    return (201);
}

int     Response::check_POST( void )
{
    if ((this->_Serv.get_cgi().size() > 0) && (extension(this->_location) == "php" || extension(this->_location) == "py"))
            return (cgi_POST());
    std::string tmp;

    tmp = (this->_location_index == -1) ? this->_Serv.get_upload_path() : this->_Serv.get_location(this->_location_index).get_upload_path();
    int help = (this->_location_index == -1) ? (this->_Serv.get_client_max_body_size()) : this->_Serv.get_location(this->_location_index).get_client_max_body_size();
    if (tmp.size() > help)
        return (403);
    if (tmp.size())
        return (Upload_file(tmp));
    if (this->_location_type == 1)
        return (403);
    else
    {
        if (this->_location[this->_location.size() - 1] != '/')
        {
            this->_header->setHeader("Location", this->_location + "/");
            return (301);
        }
        else
            return (handle_POST_Dir());
    }
}
//*********************************************DELETE*********************************************//

int     Response::file_DELETE( void )
{
    std::string tmp = "rm " + this->_location;
    if (system(tmp.c_str()))
        return (500);
    return (204);
}

int     Response::cgi_DELETE( void )
{
    if (check_CGI())
        return (CGI()); // 204 !!
    else
        return (file_DELETE());
}

int     Response::DELETE_all_Folder( void )
{
    std::string tmp = "rm -rf " + this->_location;
    if (system(tmp.c_str()))
        return (403);
    return (204);
}

int     Response::handle_DELETE_Dir( void )
{
    if (this->_Serv.get_cgi().size() > 0)
    {
        std::vector<std::string> tmp;

        if (this->_location_index == -1)
            tmp = this->_Serv.get_index();
        else
            tmp = this->_Serv.get_location(this->_location_index).get_index();
        if (tmp.size() > 0)
        {
            if (check_CGI())
                return (CGI()); // 204 !!
        }
        else
            return (403);
    }
    else
        return (DELETE_all_Folder());
    return (500);
}

int     Response::check_DELETE( void )
{
    if (this->_location_type == 1) // file
        return (cgi_DELETE());
    else if (this->_location_type == 2) // directory
    {
        if (this->_location[this->_location.size() - 1] != '/')
            return (409);
        else
            return (handle_DELETE_Dir());
    }
    return (404);
}

//************************************************************************************************//

int    Response::check_methods( void )
{
    std::string             methods[3] = {"GET", "POST", "DELETE"};
    int                     (Response::*funct[3])( void ) = {&Response::check_GET, &Response::check_POST, &Response::check_DELETE};
    std::vector<string>     tmp;

    if (this->_location_index == -1)
        tmp = this->_Serv.get_allowed_methods();
    else
        tmp = this->_Serv.get_location(this->_location_index).get_methods();
    for (std::vector<std::string>::iterator it = tmp.begin(); it != tmp.end(); it++)
    {
        if ( this->_request.get_method() == *it )
        {
            for (int i = 0; i < 3; i++)
            {
                if (this->_request.get_method() == methods[i])
                    return ((this->*funct[i])());
            }
        }
    }

    return (405);
}

int    Response::statuscode( void )
{
    if (this->_request.body_len == -1)
        return (400);
    else if (check_location() == 2)
        return (301);
    else if (check_location() == 0)
        return (404);
    else
        return (check_methods());
}

void    help_show_data(Request req)
{
    std::cout << "*****************************************" << std::endl;
    std::cout << "The is rqmethod : " << req.rqmethod << std::endl;
    std::cout << "The is location : " << req.location << std::endl;
    std::cout << "The is vrs : " << req.vrs << std::endl;
    
    std::map<std::string,std::string> tmp = req.headers;
    for (std::map<std::string,std::string>::iterator it= tmp.begin(); it!= tmp.end(); ++it)
        std::cout << "The is headers : " << it->first << " => " << it->second << std::endl;

    std::cout << "The is body : " << req.body << std::endl;
    std::cout << "The is query : " << req.query <<  std::endl;
    std::cout << "The is body_len : " << req.body_len <<  std::endl;
    std::cout << "*****************************************" << std::endl;
}

void    help_show_data_serv(server ser)
{
    std::cout << "*****************************************" << std::endl;
    std::cout << "****************SERVER*******************" << std::endl;
    for (int i = 0; i < ser.get_name_size(); i++)
        std::cout << "The name N" << i << " : " << ser.get_name(i) << std::endl;

    std::cout << "The listen_port : " << ser.get_listen_port() << std::endl;
    
    std::cout << "The listen_host : " << ser.get_listen_host() << std::endl;

    {
        std::vector<std::string> tmp = ser.get_allowed_methods();
        for (std::vector<std::string>::iterator i = tmp.begin(); i != tmp.end(); i++)
            std::cout << "The allowed_methods : " << *i << std::endl;
    }
    
    {
        std::vector<std::string> tmp = ser.get_index();
        for (std::vector<std::string>::iterator i = tmp.begin(); i != tmp.end(); i++)
            std::cout << "The index : " << *i << std::endl;
    }
    
    std::cout << "The upload_path : " << ser.get_upload_path() << std::endl;
    
    {
        std::map<std::string, std::string> tmp = ser.get_error_pages();
        for (std::map<std::string, std::string>::iterator it = tmp.begin(); it != tmp.end(); it++)
            std::cout << "The Error page : " << it->first << " and his path : " << it->second << std::endl;
    }

    {
        std::map<std::string, std::string> tmp = ser.get_redirections();
        for (std::map<std::string, std::string>::iterator it = tmp.begin(); it != tmp.end(); it++)
            std::cout << "The Redirections : " << it->first << " and his path : " << it->second << std::endl;
    }

    std::cout << "The root : " << ser.get_root() << std::endl;
    std::cout << "The client max body size : " << ser.get_client_max_body_size() << std::endl;
    std::cout << "The auto index : " << bool(ser.get_autoindex()) << std::endl;
    std::cout << "***************/SERVER*******************" << std::endl << std::endl;
    std::cout << "***************location******************" << std::endl;
    
    {
        std::vector<location> tmp = ser.get_location();
        for (std::vector<location>::iterator it = tmp.begin(); it != tmp.end(); it++)
        {
            std::cout << "The name : " << it->get_name() << std::endl;
            std::cout << "The location path : " << it->get_locations_path() << std::endl;
            std::vector<std::string> tmp_methods = it->get_methods();
            for (std::vector<std::string>::iterator itv = tmp_methods.begin(); itv != tmp_methods.end(); itv++)
                std::cout << "The allowed_methods : " << *itv << std::endl;
            std::cout << "The root : " << it->get_root() << std::endl;
            std::cout << "The client max body size : " << it->get_client_max_body_size() << std::endl;
            std::vector<std::string> loc_index = it->get_index();
            for (std::vector<std::string>::iterator i = loc_index.begin(); i != loc_index.end(); i++)
                std::cout << "The index : " << *i << std::endl;
            std::cout << "The autoindex : " << bool(it->get_autoindex()) << std::endl;
            std::cout << "The upload path : " << it->get_upload_path() << std::endl << std::endl;
            std::cout << "*****************************************" << std::endl;
        }
    }

    std::cout << "**************/location******************" << std::endl << std::endl;
    std::cout << "*****************cgi*********************" << std::endl;
    
    {
        std::vector<cgi> tmp = ser.get_cgi();
        for (std::vector<cgi>::iterator it = tmp.begin(); it != tmp.end(); it++)
        {
            std::cout << "The cgi name : " << it->get_cgi_name() << std::endl;
            std::cout << "The cgi path : " << it->get_cgi_path() << std::endl << std::endl;;
            std::cout << "*****************************************" << std::endl;
        }
    }
    
    std::cout << "****************/cgi*********************" << std::endl << std::endl;
    
    
    
    std::cout << "*****************************************" << std::endl;
}

std::string Response::get_Response( void )
{
    FirstLine   FirstLine(this->_request);

    // help_show_data(this->_request);
    // help_show_data_serv(this->_Serv);
    int i = 0;
    i = statuscode();
    errorsPages(i);
    if (this->_is_cgi && (i == 200))
        return (this->_Body);
    std::cout << FirstLine.First_Line(i) << this->_Body  << std::endl;
    return (FirstLine.First_Line(i) + this->_header->getHeader() + this->_Body);
}
