#include <iostream>
#include "hiredis.h"
using namespace std;

redisContext *_conn = NULL;

void init_redis()
{
	const char *hostname = "127.0.0.1";
	int port = 6379;
	struct timeval timeout = { 2, 500000 }; // 2.5 second
	_conn = redisConnectWithTimeout(hostname, port, timeout);

	if( _conn == NULL || _conn->err ){
		if( _conn ){
			printf("Connection error: %s\n", _conn->errstr);
			redisFree(_conn);
		}else{
			printf("Connection error: can not allocate redis context\n");
		}
	}else{
        printf("init redis success.\n");
    }
}

void reply_print(redisReply *reply)
{
    if(reply->type == REDIS_REPLY_ARRAY){
        cout << "REDIS_REPLY_ARRAY" << endl;
        for(int i = 0; i < reply->elements; i++){
            reply_print(reply->element[i]);
        }      
    }else if(reply->type == REDIS_REPLY_STRING){
        cout << "REDIS_REPLY_STRING" << endl; 
        string result(reply->str);
        cout << "result: " << result << endl;
    }else if(reply->type == REDIS_REPLY_INTEGER){
        cout << "REDIS_REPLY_INTEGER" << endl; 
        cout << reply->integer << endl;
    }else if(reply->type == REDIS_REPLY_NIL){
        cout << "REDIS_REPLY_NIL" << endl; 
    }else if(reply->type == REDIS_REPLY_STATUS){
        cout << "REDIS_REPLY_STATUS" << endl; 
        string result(reply->str);
        cout << "result: " << result << endl;
    }else if(reply->type == REDIS_REPLY_ERROR){
        cout << "REDIS_REPLY_ERROR" << endl; 
        string result(reply->str);
        cout << "result: " << result << endl;
    }else{
        cout << "reply type error!" << endl;
    }
}

void reply_test()
{
    string insertsql = "SADD keylist list1 list2 list3";  
    string searchsql = "SMEMBERS keylist";
    string delsql = "del keylist";
    string insertsql1 = "mset key1 value1 key2 value2 key3 value3";
    string getsql1 = "mget key1 key2 key4 key3";
    string getsql2 = "mget key1 key2 key3";
    string delsql1 = "del key1 key2 key3";
    
    cout << "==========test sadd: (empty list or set)" << endl; 
    redisReply *reply = (redisReply*)redisCommand(_conn, searchsql.c_str());
    reply_print(reply);
    freeReplyObject(reply);

    cout << "==========test sadd: insert" << endl; 
    reply = (redisReply*)redisCommand(_conn, insertsql.c_str());
    reply_print(reply);
    freeReplyObject(reply);
        
    cout << "==========test sadd: del" << endl; 
    reply = (redisReply*)redisCommand(_conn, delsql.c_str());
    reply_print(reply);
    freeReplyObject(reply);

    cout << "==========test mset: set" << endl; 
    reply = (redisReply*)redisCommand(_conn, insertsql1.c_str());
    reply_print(reply);
    freeReplyObject(reply);

    cout << "==========test mset: get" << endl; 
    reply = (redisReply*)redisCommand(_conn, getsql1.c_str());
    reply_print(reply);
    freeReplyObject(reply);

    cout << "==========test mset: get" << endl; 
    reply = (redisReply*)redisCommand(_conn, getsql2.c_str());
    reply_print(reply);
    freeReplyObject(reply);

    cout << "==========test mset: del" << endl; 
    reply = (redisReply*)redisCommand(_conn, delsql1.c_str());
    reply_print(reply);
    freeReplyObject(reply);
}

void sadd_test()
{
    string listsql = "sadd listkey list1key list2key list3key";
    string list1sql = "sadd list1key value11 value12 value13";
    string list2sql = "sadd list2key value21 value22 value23";
    string list3sql = "sadd list3key value31 value32 value33";
    string getlist1sql = "SMEMBERS listkey";
    string getlist2sql = "SMEMBERS list4key";
    string delsql = "del listkey list1key list2key list3key";

    cout << "==========test sadd: list" << endl; 
    redisReply *reply = (redisReply*)redisCommand(_conn, listsql.c_str());
    reply_print(reply);
    freeReplyObject(reply);

    cout << "==========test sadd: list1" << endl; 
    reply = (redisReply*)redisCommand(_conn, list1sql.c_str());
    reply_print(reply);
    freeReplyObject(reply);

    cout << "==========test sadd: list2" << endl; 
    reply = (redisReply*)redisCommand(_conn, list2sql.c_str());
    reply_print(reply);
    freeReplyObject(reply);

    cout << "==========test sadd: list3" << endl; 
    reply = (redisReply*)redisCommand(_conn, list3sql.c_str());
    reply_print(reply);
    freeReplyObject(reply);

    cout << "==========test sadd: get" << endl; 
    reply = (redisReply*)redisCommand(_conn, getlist1sql.c_str());
    reply_print(reply);
    freeReplyObject(reply);

    cout << "==========test sadd: get" << endl; 
    reply = (redisReply*)redisCommand(_conn, getlist2sql.c_str());
    reply_print(reply);
    freeReplyObject(reply);

    cout << "==========test sadd: del" << endl; 
    reply = (redisReply*)redisCommand(_conn, delsql.c_str());
    reply_print(reply);
    freeReplyObject(reply);
}

void set_test()
{
    string setsql = "set key1 value1";
    string getsql = "get key1";
    string getsql2 = "get key2";
    string delsql = "del key1";
    string delsql2 = "del key2";

    cout << "==========test del: bad" << endl; 
    redisReply *reply = (redisReply*)redisCommand(_conn, delsql2.c_str());
    reply_print(reply);
    freeReplyObject(reply);

    cout << "==========test set: ok" << endl; 
    reply = (redisReply*)redisCommand(_conn, setsql.c_str());
    reply_print(reply);
    freeReplyObject(reply);

    cout << "==========test get: ok" << endl; 
    reply = (redisReply*)redisCommand(_conn, getsql.c_str());
    reply_print(reply);
    freeReplyObject(reply);

    cout << "==========test get: ok" << endl; 
    reply = (redisReply*)redisCommand(_conn, getsql2.c_str());
    reply_print(reply);
    freeReplyObject(reply);

    cout << "==========test del: ok" << endl; 
    reply = (redisReply*)redisCommand(_conn, delsql.c_str());
    reply_print(reply);
    freeReplyObject(reply);
}

void free_redis()
{
	if( _conn != NULL){
		redisFree(_conn);
	}
}

int main()
{
    init_redis();
    reply_test();
    sadd_test();
    set_test();
    free_redis();
}
