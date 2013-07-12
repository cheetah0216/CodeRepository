import urllib
import urllib2
import cookielib
import json
import mechanize
import sys
import re
import base64
from urlparse import urlparse

def get_release_detail_info(release_id):
    '''
    init http,cookies
    '''
    cj=cookielib.CookieJar()
    cookie_support= urllib2.HTTPCookieProcessor(cj)
    opener = urllib2.build_opener(cookie_support, urllib2.HTTPHandler)
    urllib2.install_opener(opener)
    #get cookies:jsessionid
    result = urllib2.urlopen('http://10.8.33.110/cqweb/')
    
    '''
    login CQ
    '''
    postdata=urllib.urlencode({
        'loginId':'fliu',
        'password':'',
        'repository':'VCNTR',
        'tzOffset':'GMT+8:00',
        'loadAllRequiredInfo':'true',
        'cquid':'00008PbQY_R5-CbM_zTT3LnfjWa:-1'
    })
    
    headers = {
            'User-Agent':'Mozilla/5.0 (X11; Linux i686) AppleWebKit/537.31 (KHTML, like Gecko) Chrome/26.0.1410.63 Safari/537.31 AlexaToolbar/alxg-3.1'
    }
    
    req = urllib2.Request(
        url = 'http://10.8.33.110/cqweb/cqlogin.cq?action=DoLogin',
        data = postdata,
        headers = headers
    )
    
    result = urllib2.urlopen(req).read()
    #print result
    
    for index, cookie in enumerate(cj):
        #print index, cookie;
        cookies_jsessionid = cookie.value
        #print cookies_jsessionid
    
    
    '''
    connect RELDB
    '''
    postdata=urllib.urlencode({
        'userDb':'RELDB',
        'loadAllRequiredInfo':'true',
        'cquid':cookies_jsessionid
    })
    
    req = urllib2.Request(
        url = 'http://10.8.33.110/cqweb/cqlogin.cq?action=DoConnect',
        data = postdata,
        headers = headers
    )
    result= urllib2.urlopen(req).read()

    #print result
    for index, cookie in enumerate(cj):
        #print index, cookie;
        cookies_jsessionid = cookie.value
        #print cookies_jsessionid
    
    '''
    setPreference
    '''
    postdata=urllib.urlencode({
        'prefData':'{"HIDDEN_FIELDS": {"FAVORITES": {"value": "%7B%0A%09%22identifier%22%3A%20%22stableLocation%22%2C%20%0A%09%22label%22%3A%20%22title%22%2C%20%0A%09%22items%22%3A%20%5B%0A%09%09%7B%0A%09%09%09%22type%22%3A%20%22LIST%22%2C%20%0A%09%09%09%22title%22%3A%20%22Open%20Releases%22%2C%20%0A%09%09%09%22stableLocation%22%3A%20%22cq.repo.cq-query%3A33567501%40VCNTR%2FRELDB%22%2C%20%0A%09%09%09%22friendlyLocation%22%3A%20%22cq.query%3APublic%20Queries%2FRelease%20Record%20Queries%2FOpen%20Releases%40VCNTR%2FRELDB%22%2C%20%0A%09%09%09%22masterReplica%22%3A%20%22%3Clocal%3E%22%2C%20%0A%09%09%09%22insertIndex%22%3A%20%22sortByAlpha%22%0A%09%09%7D%0A%09%5D%0A%7D"}, "STARTUP_QUERY": {"value": "%7B%22loginDate%22%3A%20%22Wed%2C%2010%20Jul%202013%2012%3A17%3A58%20GMT%22%7D"}}, "generalView": {"SHOW_PROPERTIES_VIEW": {"defaultValue": "false", "uiCTRL": "CHECKBOX", "value": "false", "possibleValues": "true$false"}, "LOAD_STARTUP_QUERY_RESULT": {"defaultValue": "true", "uiCTRL": "CHECKBOX", "value": "true", "possibleValues": "true$false"}}, "resultSetview": {"NUMBER_ROWS_PER_PAGE": {"defaultValue": "20", "uiCTRL": "COMBOBOX", "value": "20", "possibleValues": "20$50$100"}, "SHOW_SPLIT_VIEW": {"defaultValue": "single", "uiCTRL": "COMBOBOX", "value": "single", "possibleValues": "single$split"}, "SHOW_CUSTOM_RECORD_VIEW": {"defaultValue": "false", "uiCTRL": "CHECKBOX", "value": "false", "possibleValues": "true$false"}, "RESULTSET_DATE_FORMAT": {"defaultValue": "longDate", "uiCTRL": "COMBOBOX", "value": "longDate", "possibleValues": "longDate$mediumDate$shortDate"}, "SORT_SERVER_CLIENT": {"defaultValue": "client", "uiCTRL": "COMBOBOX", "value": "client", "possibleValues": "client$server"}}}',
        'cquid':cookies_jsessionid
    })
    req = urllib2.Request(
        url = 'http://10.8.33.110/cqweb/cquser.cq?action=setPreference',
        data = postdata,
        headers = headers
    )
    result = urllib2.urlopen(req).read()
    #print result
    for index, cookie in enumerate(cj):
        #print index, cookie;
        cookies_jsessionid = cookie.value
        #print cookies_jsessionid
    

    '''
    get resourse ID
    '''
    postdate=urllib.urlencode({
        'action':'DoFindRecord',
        'recordId':release_id,
        'searchType':'BY_RECORD_ID',
        'cquid':cookies_jsessionid,
        'dojo.preventCache':'1373459717190'
    })
    request_url="http://10.8.33.110/cqweb/cqfind.cq?"+postdate
    result = urllib2.urlopen(request_url).read()
    #print result
    strlen=len(result)
    resourceID=result[33:strlen-2]
    #print resourceID
    

    '''
    get detail release info
    '''
    postdate=urllib.urlencode({
        'action':'GetCQRecordDetails',
        'resourceId':resourceID,
        'state':'VIEW',
        'tabIndex':'0',
        'acceptAllTabsData':'true',
        'cquid':cookies_jsessionid,
        'dojo.preventCache':'1373459723308'
    })
    request_url="http://10.8.33.110/cqweb/cqartifactdetails.cq?"+postdate
    #print url
    result = urllib2.urlopen(request_url).read()
    #print result


    '''
    write detail release tp release.json
    '''
    release=open('release.json','a')
    release.write(result)
    release.write('\n')
    release.close

def get_preb_report_url():
    release_json = file('release.tmp')
    release = json.load(release_json)
    #print release.keys()
    #print release['fields'][44]['CurrentValue'][26]
    return release['fields'][44]['CurrentValue'][26]

def get_preb_report_info(prep_report_url):



if __name__ == '__main__':
    #get_release_detail_info('RELDB00018711') 
    prep_report_url = get_preb_report_url()
    get_preb_report_info(prep_report_url)

'''
    cj=cookielib.CookieJar()
    cookie_support= urllib2.HTTPCookieProcessor(cj)
    opener = urllib2.build_opener(cookie_support, urllib2.HTTPHandler)
    urllib2.install_opener(opener)

    headers = {
        'Accept':'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
        'Accept-Charset':'GBK,utf-8;q=0.7,*;q=0.3',
        'Accept-Encoding':'gzip,deflate,sdch',
        'Accept-Language':'zh-CN,zh;q=0.8',
        'Authorization':'NTLM TlRMTVNTUAADAAAAGAAYAG4AAAAYABgAhgAAAAAAAABAAAAACAAIAEAAAAAmACYASAAAAAAAAAAAAAAABYIIAGYAbABpAHUAbABpAHUAZgBlAGkALQBPAHAAdABpAFAAbABlAHgALQAzADYAMADIU2CNnBj0bQAAAAAAAAAAAAAAAAAAAADfX4LZsiP/oIuqLwTAN385eATEHaqBMDw=',
        'Cache-Control':'max-age=0',
        'Connection':'keep-alive',
        'Host':'us-dnv-sp01',
        'User-Agent':'Mozilla/5.0 (X11; Linux i686) AppleWebKit/537.31 (KHTML, like Gecko) Chrome/26.0.1410.63 Safari/537.31'
    }

    hearders1 = {
        'Accept':'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
        'Accept-Charset':'GBK,utf-8;q=0.7,*;q=0.3',
        'Accept-Encoding':'gzip,deflate,sdch',
        'Accept-Language':'zh-CN,zh;q=0.8',
        'Cache-Control':'max-age=0',
        'Connection':'keep-alive',
        'Cookie':'WSS_KeepSessionAuthenticated=80',
        'Host':'us-dnv-sp01',
        'If-Modified-Since':'Mon, 24 Jun 2013 09:59:33 GMT',
        'If-None-Match':'"{73F095F2-48DD-46FE-A5AF-3F6F81A10B1B},3"',
        'Referer':'http://10.8.33.110/cqweb/',
        'User-Agent':'Mozilla/5.0 (X11; Linux i686) AppleWebKit/537.31 (KHTML, like Gecko) Chrome/26.0.1410.63 Safari/537.31 AlexaToolbar/alxg-3.1'
    }
    req = urllib2.Request(
            url = prep_report_url,
            headers = hearders1
    )
    
    result= urllib2.urlopen(req).read()

    print result
'''
