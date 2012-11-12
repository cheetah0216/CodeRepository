import urllib.request
import platform
import socket
import fileinput
import sys

hostsURL = "https://smarthosts.googlecode.com/svn/trunk/hosts"
hostName = socket.gethostname()
sysInfo = platform.system()

def UsePlatform():
  global sysInfo
  if(sysInfo == "Windows"):
    strDes = "C:\Windows\System32\drivers\etc\hosts"
  if(sysInfo == "Linux"):
    strDes = "/etc/hosts"
  return strDes
    
def LinuxPlatform(strDir):
  replaceStr="localhost"
  for line in fileinput.input(strDir, inplace=1):
    line = line.replace(replaceStr, hostName)   
    sys.stdout.write(line)

def WriteHosts(strDes):
  # get code of given URL as html text string
  # Python3 uses urllib.request.urlopen()
  # instead of Python2's urllib.urlopen() or urllib2.urlopen()
  getHosts = urllib.request.urlopen(hostsURL)
  mybytes = getHosts.read()

  # note that Python3 does not read the html code as string
  # but as html code bytearray, convert to string with
  strHosts = mybytes.decode("utf8")

  FileHosts = open(strDes, "w")
  FileHosts.write(strHosts)
  FileHosts.close()
  getHosts.close()

def main():
  strDes = UsePlatform()
  WriteHosts(strDes)
  # support linux platform
  if(sysInfo == "Linux"):
    LinuxPlatform(strDes)

if __name__ == "__main__":
  main()






