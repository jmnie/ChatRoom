#include "MysqlDataBase.h"
#include "muduo/base/Logging.h"
int MysqlDataBase::connect()
{
    mysql = mysql_init(NULL);//initialize database
    if(!mysql)
    {
        LOG_ERROR<<"mysql init falied";
        return -1;
    }

    mysql = mysql_real_connect(mysql,IP, "root", "140226", "ChatRoom", 0, NULL, 0);//connected to database

    if(mysql)
    {
        LOG_INFO<<"MySQL connection success";
    }
    else
    {
        LOG_WARN<<" MySQL connection failed";
        return -1;
    }
    return 0;
}
int MysqlDataBase::sqlQuery(const char *query)
{
	int res=mysql_query(mysql, "set names utf8");
	if(res!=0)
	{
		LOG_INFO<<"mysql_query set utf8 error";
		return -1;
	}
    res=mysql_query(mysql,query);
    if(res)
    {
        return -1;
    }
    return 0;
}
void MysqlDataBase::doOffline(const TcpConnectionPtr& conn)
{
	auto it=nameMap_.find(conn);
	char query[100];
	snprintf(query,sizeof(query),"select online from UserInfo where username='%s'",(it->second).c_str());
	int ret=sqlQuery(query);
	if(ret==-1)
	{
		LOG_ERROR<<"doOffline select error:"<<mysql_error(mysql);
	}
	res_ptr=mysql_store_result(mysql);
	sqlrow=mysql_fetch_row(res_ptr);
	if(sqlrow&&(atoi(sqlrow[0])==1))
	{
		memset(query,0,sizeof(query));
		snprintf(query,sizeof(query),"update UserInfo set online=%d where username='%s'",0,(it->second).c_str());
		ret=sqlQuery(query);
		if(ret==-1)
		{
			LOG_ERROR<<"doOffline update error:"<<mysql_error(mysql);
		}
	}
	mysql_free_result(res_ptr);
	nameMap_.erase(conn);
}
string MysqlDataBase::parseMessageAndOperation(const TcpConnectionPtr& conn,const string& buff)
{
    std::string  strclientmsg;
    if(buff[0] == REGISTER)
    {
        std::string rec(buff);
        if(rec.size()==0)
        {
            std::cout<<"Register substr error"<<std::endl;
        }
        auto it = rec.find('\t');


        char name[20];
        strcpy(name,rec.substr(1,it-1).c_str());

        char password[30];
        strcpy(password,rec.substr(it+1, rec.size()-1).c_str());

        char query[100];
        sprintf(query, "select username from UserInfo where username = '%s'", name);

        int ret;

        ret = sqlQuery(query);

        res_ptr = mysql_store_result(mysql); 
        sqlrow = mysql_fetch_row(res_ptr);
        if(sqlrow)
        {

            strclientmsg += "The name has been registered";
        }
        else
        {
            memset(query, 0, sizeof(query));
            
            sprintf(query, "insert into UserInfo values('%s', '%s',%d,%d)", name, password,0,0);

            ret = sqlQuery(query);
            if(ret == -1)
            {
                LOG_ERROR<<"insert error :"<<mysql_error(mysql);
            }
            else
            {
                //Regsiter Sucessfully
                //Create a user list
                memset(query, 0, sizeof(query));
                sprintf(query, "create table %s (friends char(30));",name);

                ret=sqlQuery(query);
                if(ret==-1)
                {
                    LOG_ERROR<<"create table error :"<<mysql_error(mysql);
                }
                //add self to user list
                memset(query, 0, sizeof(query));
                sprintf(query, "insert into %s values('%s')", name, name);
                ret=sqlQuery(query);
                if(ret==-1)
                {
                    LOG_ERROR<<"insert error :"<<mysql_error(mysql);
                }
                strclientmsg += "REGISTER SUCCESS";
                // continue;
                if(mysql_errno(mysql))
                {
                    LOG_ERROR<<"retrive error :"<<mysql_error(mysql);
                }
            }
        }
        mysql_free_result(res_ptr);
    }
    //login
    else if(buff[0] == LOGIN)
    {
        std::string rec(buff);
        if(rec.size()==0)
        {
            std::cout<<"LOGIN substr error"<<std::endl;
        }
        auto it = rec.find('\t');
        char name[20];
        strcpy(name,rec.substr(1,it-1).c_str());
        char password[30];
        strcpy(password,rec.substr(it+1, rec.size()-1).c_str());
        char query[100];
        sprintf(query, "select password from UserInfo where username = '%s'",name);
        sqlQuery(query);

        res_ptr = mysql_store_result(mysql);
        sqlrow = mysql_fetch_row(res_ptr);
        if(!sqlrow)
        {
            strclientmsg += "You have to register first";
        }
        else
        {
            
            if(strcmp(sqlrow[0], password) == 0)
            {
                strclientmsg += "LOG IN SUCCESS";
				std::string namestr(name);
				nameMap_.insert(make_pair(conn,namestr));
                //std::cout<<conn->name();
                //login successfully

                mysql_free_result(res_ptr);
                
				memset(query,0,sizeof(query));
                sprintf(query,"update UserInfo set online=%d where username='%s'",1,name);
                sqlQuery(query);
            }
            else
            {
                strclientmsg += "password is wrong";
            }
            if(mysql_errno(mysql))
            {
                LOG_ERROR<<"Retrive error :"<<mysql_error(mysql);
            }

        }
        //mysql_free_result(res_ptr);
    }
    else if(buff[0]==FRIENDSLIST)
    {
        char query[100];
        char name[20];
        std::string rec(buff);
        if(rec.size()==0)
        {
            std::cout<<"friendlist substr error"<<std::endl;
        }
        //std::cout<<"FriendList ::rec "<<rec<<std::endl;
        strcpy(name,rec.substr(1,rec.size()-1).c_str());
        //std::cout<<"name "<<name<<std::endl;
        memset(query,0,sizeof(query));
        sprintf(query,"select *from %s",name);
        int ret=sqlQuery(query);
        if(ret==-1)
        {
            LOG_ERROR<<"select friends error :"<<mysql_error(mysql);
        }
        res_ptr=mysql_store_result(mysql);
        int rows=(int)mysql_num_fields(res_ptr);

        std::string friendsmsg;
        int count=0;
        std::string tempstr;
        while((sqlrow=mysql_fetch_row(res_ptr)))
        {
            int i;
            for(i=0;i<rows;i++)
            {
                friendsmsg+=sqlrow[i];
                friendsmsg+=":";

                tempstr+=friendsmsg;

                friendsmsg.clear();
            }
            count++;
        }
        char str[5];
        sprintf(str,"%d",count);
        tempstr+=str;
        //std::cout<<"Friendlist tempstr: "<<tempstr<<std::endl;
        conn->send(tempstr);
        mysql_free_result(res_ptr);

    }
    //ONLINESTATE
    else if(buff[0]==ONLINESTATE)
    {

        char query[100];
        sprintf(query,"select username,online,pic from UserInfo");
        sqlQuery(query);
        res_ptr=mysql_store_result(mysql);
        int count=0;
        std::string namemsg;
        std::string onlinemsg;
        std::string picmsg;
        std::string allmsg;
        std::string tempstr;
        while((sqlrow=mysql_fetch_row(res_ptr)))
        {
            namemsg+=sqlrow[0];
            onlinemsg+=sqlrow[1];
            picmsg+=sqlrow[2];
            allmsg+=namemsg+","+onlinemsg+","+picmsg+",:";
            tempstr+=allmsg;

            namemsg.clear();
            onlinemsg.clear();
            picmsg.clear();
            allmsg.clear();
            count++;
        }
        char str[5];
        sprintf(str,"#%d#",count);
        tempstr+=str;
		//std::cout<<tempstr<<std::endl;
        conn->send(tempstr);
        mysql_free_result(res_ptr);
    }
    else if(buff[0]==PICCHANGE)
    {
        std::cout<<"PICHANGE buff: "<<buff<<std::endl;
        std::string rec(buff);
        if(rec.size()==0)
        {
            std::cout<<"PICCHANGE substr error"<<std::endl;
        }
        auto it=rec.find(':');
        char name[20];
        int pic,ret;
        char query[100];
        std::cout<<"PICCHANGE rec: "<<rec<<std::endl;
        strcpy(name,rec.substr(1,it-1).c_str());
        std::cout<<"name "<<name<<std::endl;
        pic=atoi(rec.substr(it+1,rec.size()-it-1).c_str());
        std::cout<<"pic "<<pic<<std::endl;
        sprintf(query,"update UserInfo set pic=%d where username='%s'",pic,name);
        ret=sqlQuery(query);
        if(ret==-1)
        {
            LOG_ERROR<<"update pic error :"<<mysql_error(mysql);
        }
    }
    //Chat info
    else if(buff[0] == MESSAGE)
    {
        strclientmsg += buff;
    }
    // TODO:add friend information
    else if(buff[0] == ADDFRIEND)
    {
        std::string rec(buff);
        char query[100];
        char fromname[20],toname[20];
        auto it=rec.find('+');
        strcpy(fromname,rec.substr(1,it-1).c_str());
        strcpy(toname,rec.substr(it+1,rec.size()-1).c_str());
        sprintf(query,"select username from UserInfo where username='%s'",toname);
        sqlQuery(query);
        res_ptr = mysql_store_result(mysql);
        sqlrow = mysql_fetch_row(res_ptr);
        mysql_free_result(res_ptr);
        if(!sqlrow)
        {
            strclientmsg+="The name is wrong";
        }
        else
        {
            memset(query,0,sizeof(query));
            sprintf(query,"select friends from %s where friends='%s'",fromname,toname);
            sqlQuery(query);
            res_ptr=mysql_store_result(mysql);
            sqlrow=mysql_fetch_row(res_ptr);
            mysql_free_result(res_ptr);
            if(sqlrow)
            {
                strclientmsg+="you are have been friends!";
            }
            else
            {
				TcpConnectionPtr Connection;
				std::string namestr(toname);
				for(auto it=nameMap_.begin();it!=nameMap_.end();++it)
                {
                    if(it->second==namestr)
                    {
                        Connection=it->first;
                    }
                }
                std::string msg;
                msg+="*AdDR. ";

                char tempstr[20];
                sprintf(tempstr,"%s+%s",fromname,toname);
                msg+=tempstr;
                //std::cout<<"msg: "<<msg<<std::endl;
                Connection->send(msg);
                strclientmsg+="message has been sended";
                //mysql_free_result(res_ptr);
            }
        }
    }
    else if(buff[0]==ACCEPT)
    {

        std::string rec(buff);
        auto it=rec.find('\t');
        char fromname[20];
        char toname[20];
        char query1[100];
        char query2[100];
        int ret;
        strcpy(fromname,rec.substr(1,it-1).c_str());
        strcpy(toname,rec.substr(it+1,rec.size()-(it+19)).c_str());
        std::cout<<"fromname "<<fromname<<"s"<<std::endl;
        std::cout<<"toname "<<toname<<"s"<<std::endl;
        memset(query1,0,sizeof(query1));
        memset(query2,0,sizeof(query2));
        sprintf(query1,"insert into %s values('%s')",fromname,toname);
        sprintf(query2,"insert into %s values('%s')",toname,fromname);

        ret=sqlQuery(query1);
        ret=sqlQuery(query2);
        
        if(ret == -1)
        {
            LOG_ERROR<<"insert error :"<<mysql_error(mysql);
        }
        std::string str="*ACCEPT.";
		TcpConnectionPtr Connection;
		std::string namestr(fromname);
		for(auto it=nameMap_.begin();it!=nameMap_.end();++it)
		{
			if(it->second==namestr)
			{
				Connection=it->first;
			}
		}
        Connection->send(str);
        strclientmsg+=buff;
        //mysql_free_result(res_ptr);
    }
    else if(buff[0]==REFUSE)
    {

        std::string rec(buff);
        char fromname[20];
        strcpy(fromname,rec.substr(1,rec.size()-1).c_str());
        std::string msg="your requet had been refused...";
		TcpConnectionPtr Connection;
		std::string namestr(fromname);
		for(auto it=nameMap_.begin();it!=nameMap_.end();++it)
		{
			if(it->second==namestr)
			{
				Connection=it->first;
			}
		}
        Connection->send(msg);
    }
    else
    {
        strclientmsg+=buff;
    }

    return string(strclientmsg);

}
