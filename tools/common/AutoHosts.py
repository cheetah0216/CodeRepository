import urllib.request
import platform
import socket
import fileinput
import sys
import os

hostsURL = "https://smarthosts.googlecode.com/svn/trunk/hosts"
hostName = socket.gethostname()
sysInfo = platform.system()
strDes = ""
strUser = ""
strfliu = os.environ['LF']

def UsePlatform():
  global sysInfo
  global strDes
  global strUser
  if(sysInfo == "Windows"):
    strDes = "C:\Windows\System32\drivers\etc\hosts"
    strUser = "C:\Windows\System32\drivers\etc\PrivateHosts"
  if(sysInfo == "Linux" || sysInfo == "Darwin"):
    strDes = "/etc/hosts"
    strUser = strflu + "/.PrivateHosts"
  if(os.path.exists(strUser) == False):
    files = open(strUser, "w")
    files.write("")
    files.close()

def LinuxPlatform(strDir):
  replaceStr = "localhost"
  for line in fileinput.input(strDir, inplace=1):
    line = line.replace(replaceStr, hostName)   
    sys.stdout.write(line)

def OSXPlatform(strDie):
  

def WriteHosts():
  global strDes
  # get code of given URL as html text string
  # Python3 uses urllib.request.urlopen()
  # instead of Python2's urllib.urlopen() or urllib2.urlopen()
  getHosts = urllib.request.urlopen(hostsURL)
  mybytes = getHosts.read()
  # note that Python3 does not read the html code as string
  # but as html code bytearray, convert to string with
  strHosts = mybytes.decode("utf8")
  # Add User Hosts
  FileUser = open(strUser, "r")
  contents = FileUser.read()
  FileUser.close()
  strHosts = strHosts + "\n" + contents

  FileHosts = open(strDes, "w")
  FileHosts.write(strHosts)
  FileHosts.close()
  getHosts.close()


def main():
  UsePlatform()
  WriteHosts()
  # support linux platform
  if(sysInfo == "Linux"):
    LinuxPlatform(strDes)
  if(sysInfo == "Darwin"):
    OSXPlatform(strDes)

if __name__ == "__main__":
  main()






