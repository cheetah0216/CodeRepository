#include "redismanage.h"

RedisMng::RedisMng()
{
	DEBUG_PL(LOG_ERROR, "init redis...\n");

	const char *hostname = "127.0.0.1";
	int port = 6380;
	struct timeval timeout = { 2, 500000 }; // 2.5 second
	_conn = redisConnectWithTimeout(hostname, port, timeout);

	if( _conn == NULL || _conn->err ){
		if( _conn ){
			DEBUG_PL(LOG_ERROR, "Connection error: %s\n", _conn->errstr);
			redisFree(_conn);
		}else{
			DEBUG_PL(LOG_ERROR, "Connection error: can not allocate redis context\n");
		}
	}else{
		DEBUG_PL(LOG_ERROR, "init redis success.\n");
		/*
		redisReply *reply;
		uint64_t day = CTimeOutAlarm::_ins.get_zeroclock_time(time);
		string key = "latest_day_key";
		reply = (redisReply *)redisCommand(_conn, "SET %s %lu",key.c_str(), day); 
		//DEBUG_PL(LOG_DEBUG, "latest_day_key, SET: %s\n", reply->str);
		freeReplyObject(reply);

		string key_list = "day_list";
		string day_cmd_list = to_str<uint64_t>(day) + "_cmd_list";
		reply = (redisReply *)redisCommand(_conn, "SADD %s %s", key_list.c_str(), day_cmd_list.c_str());
		//DEBUG_PL(LOG_DEBUG, "day_list, SET: %s\n", reply->str);
		freeReplyObject(reply);
		*/
	}
}

RedisMng::~RedisMng()
{
	if( _conn != NULL){
		redisFree(_conn);
	}
}	

void RedisMng::write_momentscache_to_redis(WaitVerifyMomentsReq &reqbody)
{
	string momentsid = reqbody.item().momentsid();
	VerifyMomentsCache cacheitem;
	cacheitem.set_momentsid(momentsid);
	cacheitem.set_uin(reqbody.item().uin());
	cacheitem.set_optype(reqbody.item().optype());
	cacheitem.set_mask(reqbody.item().mask());
	cacheitem.set_createstamp(reqbody.item().createstamp());
	cacheitem.set_ver(reqbody.item().ver());
	string value;
	cacheitem.SerializeToString(&value);

	DEBUG_PL(LOG_DEBUG, "momentscache: redis SET %s %s \n", momentsid.c_str(), value.c_str());	
	redisReply *reply = (redisReply*)redisCommand(_conn, "SET %s %b", 
			momentsid.c_str(), 
			value.c_str(), 
			value.length());
	DEBUG_PL(LOG_DEBUG, "SET: %s\n", reply->str);
	freeReplyObject(reply);
	
	/*
	redisReply *timereply = (redisReply*)redisCommand(_conn, "EXPIRE %s %d", momentsid.c_str(), KEY_TIME);
	DEBUG_PL(LOG_DEBUG, "EXPIRE: %s\n", timereply->str);
	freeReplyObject(timereply);
	*/
}

string RedisMng::get_list_key()
{
	//key = "moments_" + "当前秒数（精确到小时）"
	//相同小时的数据在一个list中
	string listkey = "moments_";
	unsigned int curtime = time(NULL);
	unsigned int curhours = curtime - curtime % 3600;
	listkey = listkey + to_str<unsigned int>(curhours);

	return listkey;
}

void RedisMng::write_momentscachelist_to_redis(WaitVerifyMomentsReq &reqbody)
{
	string listkey = get_list_key();
	string momentsid = reqbody.item().momentsid();

	write_all_momentslist_key(listkey);


	DEBUG_PL(LOG_DEBUG, "momentslist: redis SADD %s %s\n", listkey.c_str(), momentsid.c_str());
	redisReply *reply = (redisReply*)redisCommand(_conn, "SADD %s %s", listkey.c_str(), momentsid.c_str());
	DEBUG_PL(LOG_DEBUG, "SADD: %s\n", reply->str);
	freeReplyObject(reply);
	
	/*
	redisReply *timereply = (redisReply*)redisCommand(_conn, "EXPIRE %s %d", listkey.c_str(), KEYLIST_TIME);
	DEBUG_PL(LOG_DEBUG, "EXPIRE: %s\n", timereply->str);
	freeReplyObject(timereply);
	*/
}

void RedisMng::write_all_momentslist_key(const string listkey)
{
	string key = "all_momentslist_key";
	DEBUG_PL(LOG_DEBUG, "all_momentslist_key: redis SADD %s %s\n", key.c_str(), listkey.c_str());
	redisReply *reply = (redisReply*)redisCommand(_conn, "SADD %s %s", key.c_str(), listkey.c_str());
	DEBUG_PL(LOG_DEBUG, "SADD: %s\n", reply->str);
	freeReplyObject(reply);
}

void RedisMng::write_moments(WaitVerifyMomentsReq &reqbody)
{
	if(reqbody.item().momentsid() == ""){
		DEBUG_PL(LOG_ERROR, "bad momentsid\n");
		return ;
	}

	write_momentscache_to_redis(reqbody);
	write_momentscachelist_to_redis(reqbody);
}


void RedisMng::get_listkey_bytime(unsigned int starttime, unsigned int endtime, set<string> &listkey) 
{
	unsigned int starthours = starttime - starttime % 3600;
	unsigned int endhours = endtime - endtime % 3600;

	for(unsigned int time = starthours; time <= endhours; time = time + 3600){
		string momentslistkey = "moments_" + to_str<unsigned int>(time);
		DEBUG_PL(LOG_DEBUG, "momentslistkey:%s\n", momentslistkey.c_str());
		listkey.insert(momentslistkey);
	}
}

void RedisMng::get_moments(unsigned int starttime, unsigned int endtime, set<string> &momentsidlist)
{
	set<string> listkey;
	get_listkey_bytime(starttime, endtime, listkey);
	
	string sql = "mget "
	set<string>::iterator it = listkey.begin();
	for(; it != listkey.end(); it++){
		sql += *it;
	}
	
	set<string> tmpmomentslist;
	if(listkey.size() != 0){
		DEBUG_PL(LOG_DEBUG, "redis sql: %s\n", sql.c_str());
		redisReply *reply = (redisReply*)redisCommand(_conn, sql.c_str());

		if (reply->type == REDIS_REPLY_ARRAY) {
			for (j = 0; j < reply->elements; j++) {
				string momentsid(reply->element[j]->str);
				DEBUG_PL(LOG_DEBUG, "momentsid:%s\n", momentsid.c_str());
				tmpmomentslist.insert(momentsid);
			}
		}
		freeReplyObject(reply);

	}else{
		DEBUG_PL(LOG_ERROR, "ERROR:listkey size is 0.starttime:%d, endtime:%d\n", starttime, endtime);
	}
}
