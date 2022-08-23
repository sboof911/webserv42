
#include "../Includes/tt.hpp"
#include "../Includes/server.hpp"
#include "../Includes/sboof/Response.hpp"
#include <vector>
#include <sstream>



bool isnumber(const std::string& str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		char current = str[i];
		if (current >= '0' && current <= '9')
			continue;
		return false;
	}
	return true;
}

std::vector<std::string> split (std::string s, std::string delimiter,char *compare) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
   std:: vector<std::string> res;
   std::string val;
   std::stringstream streamData(s);
   const char separator = ' ';

   int done = 0;
   while (std::getline(streamData,val,separator))
   {
    
    int value = val.compare(compare);
    if (value == 0)
    done = 1;
     if(val.size() > 0  && done == 1)
    res.push_back(val);
   
   }
   return (res);
}

std::string removespace(std::string s)
{
    //traversing the string
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ')
        {
            s.erase(s.begin() + i);
            i--;
        }
    }
    return (s);
}
std::vector<std::string > extract_server_names(std::vector<std::string> text_vector,int index)
{
 std::vector<std::string> parser;
 std::vector <std::string> server_names;
 std::vector <std::string> correct_names;
    int i = 0;
    int y = 0;
    int inside = 0;
    int count = 0;
    while ( i < text_vector.size())
    {  
        if(text_vector[i].compare("server") == 0)
           count++;
        if ( count == index)
        {
        parser = split(text_vector[i]," ",(char *)"server_names");
        y = 0;
        while (y < parser.size())
        {
            parser[y] = removespace(parser[y]);
            if (parser[y] == "server_names")
            {
                if (inside == 1)
             {
                std::cerr << "ERROR ! Too many server_names in config files !" << std::endl;
                exit(1);
            }
                server_names = split (text_vector[i]," ",(char *)"server_names");
        if(!server_names.empty() && server_names.size() > 1 )
        {
            server_names.erase(server_names.begin());
        }
        else 
        {
            std::cout << " Config file error :  No servernames found ! , IDX " << index << std::endl;
            exit(1);
        }
           inside = 1;
         }
            y++;
        }
        }
    i++;
    }
   
    return (server_names);
}

int extract_server_port(std::vector<std::string> text_vector,int index)
{
 std::vector<std::string> parser;
 std::vector <std::string> server_names;
 std::stringstream ss;

 int delimitier = 0;
    int i = 0;
    int y = 0;
    int inside = 0;
    int num = -1;
    int count = 0;
    while ( i < text_vector.size())
    {  
          if(text_vector[i].compare("server") == 0)
     {
           count++;
    }
        if ( count == index)
        {
        parser = split(text_vector[i]," ",(char *)"listen");
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("listen") == 0)
            {

                if (inside == 1)
             {
                std::cerr << "ERROR ! Too many Listen in config files !" << std::endl;
            exit(1);
            }
             if( parser[y + 1].find(":") != std::string::npos)
             {
                 std::vector<std::string > port;
                 port = ft_split(parser[1],":");
                if(!port[1].empty() && isnumber(port[1]))
                    num = std::stoi(port[1]);
                else
                {
                    std::cout << "Error ! Port not defined or is not a number !" << std::endl;
                    exit(1);
                }

            }
           inside = 1;
            }
            
            y++;
        }
        }
    i++;
    }
    return (num);
}



std::string extract_server_host(std::vector<std::string> text_vector,int index)
{
     std::vector<std::string> parser;
 std::vector <std::string> tmp;
std::string server_host;

    int i = 0;
    int y = 0;
    int inside = 0;
    int delimitier = 0;
    int count = 0;
    while ( i < text_vector.size())
    {  
          if(text_vector[i].compare("server") == 0)
     {
           count++;
    }
        if ( count == index)
        {
        parser = split(text_vector[i]," ",(char *)"listen");
        y = 0;
        while (y < parser.size())
        {

            if (parser[y].compare("listen") == 0)
            {

                  if (inside == 1)
             {
                std::cerr << "ERROR ! Too many host or port  in config files ! " << std::endl;
            exit(1);
            }
             if( parser[y + 1].find(":") != std::string::npos)
             {
                 std::vector<std::string > port;
                 port = ft_split(parser[1],":");
                 if (!port[0].empty())
                server_host = port[0];
             }
               else
                server_host = parser[y + 1];

        }
            y++;

        }
        }
    i++;
    }

    return (server_host);
}


std::string extract_server_root(std::vector<std::string> text_vector,int index)
{
     std::vector<std::string> parser;
 std::vector <std::string> server_names;
 std::vector <std::string > tmp;
 std::string root;
    int i = 0;
    int y = 0;
    int inside = 0;
    int count = 0;
    int inside_loc = 0;
    while ( i < text_vector.size())
    {  
             if(text_vector[i].compare("server") == 0)
     {
           count++;
    }
        if ( count == index)
        {
                 if(text_vector[i].find("location") != std::string::npos)
                 {
                     inside_loc = 1;
                 }
                 if (text_vector[i].find("}")  != std::string::npos && inside_loc == 1)
                 inside_loc = 0;
        parser = split(text_vector[i]," ",(char *)"");
        y = 0;
        while (y < parser.size())
        {
            
            if (parser[y].compare("root") == 0 && inside_loc == 0)
            {   
                if (inside == 1)
                {
                    std::cout << "Error ! The root for this server is already defined !" << std::endl;
                    exit(1);
                }
                server_names = split (text_vector[i]," ",(char *)"root");
                tmp = server_names;
                tmp.erase(tmp.begin());
                if (tmp.size() > 0)
                    root = tmp[0];
                else
                {
                    std::cout << "root is defined but nothing is put in it !  server : " << index << std::endl;
                    exit(1);
                }
                inside = 1;
            }
            y++;
        }
        }
    i++;
    }
    return (root);

}

int    specified_methods(std::string &tmp)
{
    std::string err;
    err = "Error: ";
    err += tmp;
    err += " is not a valid word";
    if (tmp != "DELETE" && tmp != "POST" && tmp != "GET")
        {
            std::cout << "Method not allowed in config file !" << tmp  << std::endl;
            exit(1);    
        }
        return (0);
}

std::vector<std::string> extract_allowed_methods(std::vector<std::string> text_vector,int index)
{
     std::vector<std::string> parser;
 std::vector <std::string> allowed_methods;
 std::vector <std::string > correct_methods;
  std::vector <std::string> tmp;
    int i = 0;
    int y = 0;
    int inside = 0;
    int count = 0;
    int done = 0;
    int inside_loc = 0;
    while ( i < text_vector.size())
    {  
        if(text_vector[i].compare("server") == 0)
           count++;
        if ( count == index)
        {
        if(text_vector[i].find("location") != std::string::npos)
            inside_loc = 1;
        if(text_vector[i].find("}") != std::string::npos && inside_loc == 1)
        inside_loc = 0;
        parser = split(text_vector[i]," ",(char *)"allow_methods");
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("allow_methods") == 0 && inside_loc == 0)
            {
                tmp.push_back(text_vector[i]);
                allowed_methods = split_by_space(tmp);
                if (done == 1)
                {
                    std::cout << "Error ! Too many allowed methods keywork in server "  << text_vector[i]<< std::endl;
                    exit (1);
                }
              correct_methods = allowed_methods;
                done = 1;
                tmp.clear();
                correct_methods.erase(std::remove(correct_methods.begin(),correct_methods.end(),"allow_methods"));
                if(correct_methods.empty())
                {
                    std::cout<< " Error ! Allowed methods is defined in server but no value is put in it !" << std::endl;
                    exit(1);
                }
                for(std::vector<std::string>::iterator it = correct_methods.begin();it != correct_methods.end();it++)
                   specified_methods(*it);
                inside = 1;
            }
            y++;
        }
        }
    i++;
    }
    return (correct_methods);
}


std::vector<std::string> extract_server_index(std::vector<std::string> text_vector,int index)
{
     std::vector<std::string> parser;
 std::vector <std::string> server_index;
  std::vector <std::string> correct_index;
    int i = 0;
    int y = 0;
    int inside = 0;
    int count = 0;
    while ( i < text_vector.size())
    {  
           if(text_vector[i].compare("server") == 0)
           count++;
        if ( count == index)
        {
        if(text_vector[i].find("location") != std::string::npos)
        return (correct_index);
        parser = split(text_vector[i]," ",(char *)"index");
        y = 0;
        while (y < parser.size())
        {
            int i = 0;
              for(std::vector<std::string>::iterator it = parser.begin();it != parser.end();it++)
                {
                    if(i > 0)
                    correct_index.push_back(*it);
                    i++;
                }
                return(correct_index);
                inside = 1;
            y++;
        }
        }
    i++;
    }
    return (correct_index);
}

std::string extract_server_upload_path(std::vector<std::string> text_vector,int index)
{
std::vector<std::string> parser;
 std::vector <std::string> server_upload_path;
 std::vector<std::string> tmp;
 std::string upload_path;
    int i = 0;
    int y = 0;
    int inside = 0;
    int count = 0;
    int inside_loc = 0;
    while ( i < text_vector.size())
    {  
        if(text_vector[i].compare("server") == 0)
           count++;
        if ( count == index)
        {
          if(text_vector[i].find("location") != std::string::npos)
            inside_loc = 1;
        if (text_vector[i].find("}") != std::string::npos && inside_loc == 1)
        inside_loc = 0;
        parser = split(text_vector[i]," ",(char *)"upload_path");
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("upload_path") == 0 && inside_loc == 0)
            {   
                server_upload_path = split (text_vector[i]," ",(char *)"upload_path");
                tmp = server_upload_path;
                if (inside == 1)
                {
                    std::cout << "Error ! Upload path already defined ... " << std::endl;
                    exit(1);
                }
                tmp.erase(tmp.begin());
                if(tmp.size() > 0)
                upload_path = server_upload_path[1];
                else
                {
                    std::cout << "upload path defined but nothing is put in it !" << std::endl;
                    exit(1);
                }
                inside = 1;
            }
            y++;
        }
        }
    i++;
    }
    return (upload_path);
}

std::map <std::string,std::string > extract_server_errors_page1(std::vector<std::string > text_vector,int index,std::map<std::string,std::string > default_errors_page)
{
    int i = 0;
    int count = 0;
    std::map <std::string,std::string > errors_page;
    std::vector<std::string > parser;
    std::vector < std::string >test;
    errors_page = default_errors_page;
    int inside = 1;
    int y = 0;
       while ( i < text_vector.size())
    {  
            if(text_vector[i].compare("server") == 0)
           count++;
        if ( count == index)
        {
        parser = split(text_vector[i]," ",(char *)"error_page");
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("error_page") == 0)
            {
                std::cout << "ERROR PAGES" << std::endl;
                test = split (text_vector[i]," ",(char *)"error_page");
                if (test.size()  == 3)
                    errors_page[test[1]] = test[2];
            else if ( test.size() < 3)
            {
                std::cout << " Config file : No Error code  or error link  ! !,IDX :" << index  << std::endl;
                exit(1);
            }
            else if (test.size() > 3)
            {
                std::cout << "Config file : Error too many links or errors code !, IDX :" << index << std::endl;
                exit(1);
            }
                inside = 1;
                test.clear();
            }
            y++;
        }
        }
    i++;
    }
    return (errors_page);
}

std::map <std::string,std::string > extract_server_redirections1(std::vector<std::string > text_vector,int index)
{
    int i = 0;
    int count = 0;
    std::map <std::string,std::string > redirections;
    std::vector<std::string > parser;
    std::vector < std::string >test;

    int inside = 1;
    int y = 0;
       while ( i < text_vector.size())
    {  
            if(text_vector[i].compare("server") == 0)
           count++;
        if ( count == index)
        {
        parser = split(text_vector[i]," ",(char *)"redirection");
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("redirection") == 0)
            {
                test = split (text_vector[i]," ",(char *)"redirection");
                if (test.size()  == 3)
                    redirections[test[1]] = test[2];
            else if ( test.size() < 3)
            {
                std::cout << " Config file : No redirection   link  ! !,IDX :" << index  << std::endl;
                exit(1);
            }
            else if (test.size() > 3)
            {
                std::cout << "Config file :  too many  redirections links on code !, IDX :" << index << std::endl;
                exit(1);
            }
                inside = 1;
                test.clear();
            }
            y++;
        }
        }
    i++;
    }
    return (redirections);
}

long long int extract_server_max_body_size(std::vector<std::string> text_vector,int index)
{

 std::vector<std::string> parser;
 std::vector <std::string> server_names;
 std::vector <std::string > tmp;
std::string test;
 std::stringstream ss;

 int delimitier = 0;
    int i = 0;
    int y = 0;
    int inside = 0;
    int num = 0;
    int count = 0;
    int inside_loc = 0;
    int done = 0;
    while ( i < text_vector.size())
    {  
         if(text_vector[i].compare("server") == 0)
           count++;
        if ( count == index)
        {
          if(text_vector[i].find("location") != std::string::npos)
            inside_loc = 1;
     if (text_vector[i].find("}") != std::string::npos && inside_loc == 1)
        inside_loc = 0;
        parser = split(text_vector[i]," ",(char *)"client_max_body_size");
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("client_max_body_size") == 0 && inside_loc == 0)
            {
                 if (done == 1)
                {
                    std::cout << "Error ! Client max body size is already defined  in the server ... " << std::endl;
                    exit(1);
                }
                tmp = parser;
                tmp.erase(tmp.begin());
             if(tmp.size() > 0)
            {
                done = 1;
                if(isnumber(tmp[0]))
                    num = std::stoi(tmp[0]);
                else
                {
                    std::cout << " Error ! A char is present in client_max_body_size" << std::endl;
                    exit(1);
                }
            }
            else if(tmp.size() == 0)
            {
                std::cout << "client_max_body_size is defined but no value is put in it ! server index : " << index << std::endl; 
                exit(1);
                num = -1;
            }
        }
            y++;
        }
        }
    i++;
    }

if (inside == 0)
num = -1;
    return (num);
}

bool extract_server_autoindex(std::vector<std::string > text_vector,int index)
{

 std::vector<std::string> parser;

    int i = 0;
    int y = 0;
    int inside = 0;
    int done = 0;
    bool autoindex = false;
    std::vector<std::string> tmp;
    int count = 0;
    while ( i < text_vector.size())
    {  
        if(text_vector[i].compare("server") == 0)
           count++;
        if ( count == index)
        {
        parser = split(text_vector[i]," ",(char *)"autoindex");
        if(text_vector[i].find("location") != std::string::npos)
            inside = 1 ;
          if (text_vector[i].find("}") != std::string::npos && inside == 1)
        inside = 0;
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("autoindex") == 0)
            {
                if ( inside == 0)
            {
                if (done == 1)
                {
                    std::cout << "Error ! autoindex is already defined in this server ...." << std::endl;
                    exit(1);
                }
                tmp = parser;
                tmp.erase(tmp.begin());
             if(tmp.size() > 0)
                    {
               if(tmp[0].compare("on") == 0)
               autoindex = true;
               else if (tmp[0].compare("off") == 0)
               autoindex = false;
               else
                            {
                std::cout << "Error ! autoindex can only take on or off as values  not " << tmp[0] << std::endl;
                exit(1); 
                            }
                    }
            else if(tmp.size() == 0)
                            {
                std::cout << "autoindex is defined but no value is put in it ! server index : " << index << std::endl;
                exit(1);
                            }
            done = 1;
                        }
                    }
            y++;
                }
            }
    i++;
    }
    return (autoindex);
}



int extract_number_of_locations(std::vector <std::string> text_vector,int index)
{

    int i = 0;
    int y = 0;
    int inside = 0;
    int count = 0;
    int find_right_server = 0;
    bool autoindex = false;
    while ( i < text_vector.size())
    {  
           if(text_vector[i].compare("server") == 0)
           find_right_server++;
        if (find_right_server == index)
        {
    if(text_vector[i].find("location") != std::string::npos)
            count++;
        }
        i++;
    }
    return (count);
}
void check_cgi(std::string tmp)
{
    int i = 0;
    while (tmp[i])
    {
    if (tmp[0] != '.')
        break;
        if(tmp[0] == '.')
        {
            if(tmp[1] == 'p' && tmp[2] == 'y' && tmp[3] == '\0')
                return ;
            else if (tmp[1] == 'p' && tmp[2] == 'h' && tmp[3] == 'p' && tmp[i + 4] == '\0')
            return ;
        }
    i++;
    }
    if(!tmp.empty())
    std::cout << " Error ! cgi extension "  << std::endl;
    exit(1);
}

std::vector<cgi> extract_server_cgi(std::vector<std::string > text_vector,int index)
{
    std::vector<cgi> vector_cgi;
    std::vector<cgi> tt;

    cgi tmp;
    std::vector<std::string > parser;
    std::vector<std::string > cgi_path;
    std::vector<std::string> cgi_name;

    int i = 0;
    int count = 0;
    int vector_size = 0;
    int accolade = 0;
    int find_right_server = 0;
    int inside = 0;
    int path = 0;
    int name = 0;
    while ( i < text_vector.size())
    {  
           if(text_vector[i].compare("server") == 0)
           find_right_server++;
        if (find_right_server == index)
        {
            parser = split(text_vector[i]," ",(char *)"cgi");
            if (parser.size() > 0 )
            inside = 1;
            if ( inside == 1)
            {
                    check_cgi(parser[1]);
                     tmp.set_cgi_name(parser[1]);
                     name = 1;
                    cgi_path = split(text_vector[i]," ",(char *)"cgi_path");
                    if(cgi_path.size() == 2)
                   {
                    tmp.set_cgi_path(cgi_path[1]);
                     path = 1;
                    }
                  else if (cgi_path.size() == 1)
                  {
                    std::cout << " Error ! Cgi_Path defined but nothing  is put in it !" << std::endl;
                    exit(1);
                  }
                  else if (cgi_path.size() > 2)
                  {
                         std::cout << " Error ! Cgi_Path  Too many path in config file  !" << std::endl;
                    exit(1);
                  }
                    if (path == 1 && name == 1)
                    {
                        vector_cgi.push_back(tmp);
                        cgi_name.clear();
                        cgi_path.clear();
                        path = 0;
                        name = 0;
                    }
            }
        }
        i++;
    }
    return(vector_cgi);
}