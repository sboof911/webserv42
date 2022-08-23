#include "../Includes/server.hpp"

 std::vector<server> fill_server(std::vector <std::string > text_vector,int nb_of_servers)
{
   
        int length = 1;
        std::vector <server> multi_serveur;
        while ( length <= nb_of_servers )
        {
        server myserver(text_vector,length);
        if(myserver.get_listen_port() == 0)
         std::cout << " Listen port can't be equal to 0 !  this server will not be accessible . nane : " << myserver.get_name(0)  << std::endl;
        if(myserver.get_listen_port() != 0 && is_server_inside(myserver,multi_serveur) == 0)
        multi_serveur.push_back(myserver);
        // else
                //  std::cout << " Listen port can't be equal to 0 !  this server will not be accessible . nane : " << myserver.get_name(0)  << std::endl;
        length++;
        }

    return (multi_serveur);

}


void print_parsing_infos(server myserver)
{
    //  std::cout << "-----------------------Server Names : ------------------"  << std::endl;
    //     std::cout << myserver.get_name(0) << "    " << myserver.get_name(1) << "   " << myserver.get_name(2) << std::endl;
    //      std::cout << "-----------------------Server Port : ------------------"  << std::endl;
    //      std::cout << myserver.get_listen_port() << std::endl;
    //        std::cout << "-----------------------Server Host : ------------------"  << std::endl;
    //      std::cout << myserver.get_listen_host() << std::endl;
    //         std::cout << "-----------------------Server root : ------------------"  << std::endl;
    //      std::cout << myserver.get_root() << std::endl;
    //                std::cout << "-----------------------Server allowed methods : ------------------"  << std::endl;
    //  for (std::vector<std::string>::iterator it1 = myserver.get_allowed_methods().begin();it1 != myserver.get_allowed_methods().end();it1++)
    //      std::cout << *it1 << std::endl;
    //  std::cout << "-----------------------Server  Index : | ------------------"  << std::endl;
    //  for (std::vector<std::string>::iterator it2 = myserver.get_index() .begin();it2 != myserver.get_index() .end();it2++)
    //      std::cout << *it2 << std::endl;
    //  std::cout << "-----------------------Server  upload path : ------------------"  << std::endl;
    // std::cout << myserver.get_upload_path() << std::endl;
    //  std::cout << "-----------------------Server  error pages  : ------------------"  << std::endl;
    //     try
    //     {
    //     for (std::map<std::string,std::string >::iterator it3 = myserver.get_error_pages().begin();it3 != myserver.get_error_pages().end();it3++)
    //      std::cout << it3->first << it3->second << std::endl;
    //        std::cout << "-----------------------------------------------"  << std::endl;

    //     // for (std::vector<std::string>::iterator it4 = myserver.get_error_pages(1).begin();it4 != myserver.get_error_pages(1).end();it4++)
        //  std::cout << *it4 << std::endl;
        //    std::cout << "-----------------------------------------------"  << std::endl;
         
          //for (std::vector<std::string>::iterator it5 = myserver.get_error_pages(2).begin();it5 != myserver.get_error_pages(2).end();it5++)
        // std::cout << *it5 << std::endl;
        // } 
      //   catch (const std::string & exception)
      //   {
      //       std::cout << "error pages exception !" << std::endl;
      //   }
      //  try {
      //      std::cout << "-----------------------Server  redirections  pages  : ------------------"  << std::endl;
      //    for (std::vector<std::string>::iterator it3 = myserver.get_redirections()[0].begin();it3 != myserver.get_redirections()[0].end();it3++)
      //    std::cout << *it3 << std::endl;
      //      std::cout << "-----------------------------------------------"  << std::endl;
     
      //   for (std::vector<std::string>::iterator it4 = myserver.get_redirections().at(1).begin();it4 != myserver.get_redirections()[1].end();it4++)
      //    std::cout << *it4 << std::endl;
         
      //    // for (std::vector<std::string>::iterator it5 = myserver..at(2).begin();it5 != myserver..at(2).end();it5++)
      //    //std::cout << *it5 << std::endl;
      //  }
      //  catch (const std::string & exception )
      //  {
      //   std::cout << "redirections pages exception ! " << std::endl;
      //  }
        //    std::cout << "-----------------------Server  Client Max Body Size   : ------------------"  << std::endl;
        // std::cout << myserver.get_client_max_body_size() << std::endl;
        // std::cout << "-----------------------Server  AutoIndex    : ------------------"  << std::endl;
        // if (myserver.get_autoindex() == true)
        // std::cout << "autoindex on " << std::endl;
        // else if (myserver.get_autoindex() == false)
        // std::cout << "autoindex off " << std::endl;

}
int number_of_servers(std::vector <std::string > words)
{
    int i = 0;
    int count = 0;
    int accolade = 0;
    while ( i < words.size())
    {
          if (words[i] == "server" && accolade == 0)
             count++;
        if (words[i] == "{")
        ++accolade;
        if (words[i] == "}")
        --accolade;
      
        i++;
        
    }
    // std::cout << "NUMBER OF SERVERS => " << count << std::endl;
    return (count);
}
