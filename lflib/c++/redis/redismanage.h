#pragma once
#include "comm_inc.h"
#include "hiredis.h"

/*
 * Verify Redis 数据布局 
 *
 * */

/********************************************************************************
 * 审核的momnets 存储:
 * key --> value : momentsid --> VerifyMomentsCache
 *
 * message VerifyMomentsCache
 {
 optional string momentsid = 1;
 optional uint32 uin = 3; //发这条moments的用户的uin
 optional uint32 optype = 4; //是否删除
 optional uint32 mask = 5[default=0]; //MomentsFlag
 optional uint32 createstamp = 6;
 optional uint32 ver = 8;
 optional Pos pos = 9;
 }
 *
 * 待审核的momentslist 存储:
 * key --> list : 
 * string key = "moments_" + timestamp; //("一个小时内的moments在一个list内")
 * 例如:
 * moments_14234233442: momentsid1--momentsid2--momentsid3--.......
 *
 * 所有momentslist key的存储：
 * all_momentslist_key: moments_14234233442--moments_14234233442--moments_14234233442
 *******************************************************************************/

class RedisMng{
public:
	RedisMng();
	~RedisMng();

public:
	void write_moments(WaitVerifyMomentsReq &reqbody);
	void get_moments(unsigned int starttime, unsigned int endtime, set<string> &momentsidlist);

private:
	string get_list_key();
	void write_momentscache_to_redis(WaitVerifyMomentsReq &reqbody);
	void write_momentscachelist_to_redis(WaitVerifyMomentsReq &reqbody);
	void write_all_momentslist_key(const string listkey);

	void get_listkey_bytime(unsigned int starttime, unsigned int endtime, set<string> &listkey); 

public:
	static const int KEY_TIME = 1296000; //15 days
	static const int KEYLIST_TIME = 1209600; //14 days
private:
	redisContext *_conn;
};
