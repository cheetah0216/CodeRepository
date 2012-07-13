import urllib.request
import platform


hostsURL = "https://smarthosts.googlecode.com/svn/trunk/hosts"

def UsePlatform():
  sysInfo = platform.system()
  if(sysInfo == "Windows"):
    strDes = "C:\Windows\System32\drivers\etc\hosts"
  if(sysInfo == "Linux"):
    strDes = "/etc/hosts"
  return strDes
    
 
# get code of given URL as html text string
# Python3 uses urllib.request.urlopen()
# instead of Python2's urllib.urlopen() or urllib2.urlopen()
import urllib.request
getHosts = urllib.request.urlopen(hostsURL)
mybytes = getHosts.read()

# note that Python3 does not read the html code as string
# but as html code bytearray, convert to string with
strHosts = mybytes.decode("utf8")

strDes = UsePlatform()
FileHosts = open(strDes, "w")
FileHosts.write(strHosts)
FileHosts.close()
getHosts.close()







