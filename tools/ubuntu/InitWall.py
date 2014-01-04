import os

class goagent(object):
  def __init__(self):
    self.goagent_url = 'https://github.com/goagent/goagent.git'
    self.goagent_dir = os.environ['SOFT'] + '/goagent'
    self.goagent_conf = self.goagent_dir + '/local/proxy.ini'
    self.goagent_bk = self.goagent_dir + '/local/proxy.bk'
    self.goagent_conf_new = self.goagent_dir + '/local/proxy.ini_new' 
    self.goagent_server = self.goagent_dir + '/server'

  def Start(self):
    #self._init()
    #self._configure()
    self._upload()
  
  def _init(self):
    cmd = 'git clone ' + self.goagent_url + ' ' + self.goagent_dir
    os.system(cmd)

  def _configure(self):
    new_conf_file = open(self.goagent_conf_new,'w')
    with open(self.goagent_conf, 'r') as confInfo:
      for line in confInfo:
        if 'appid' in line:
          line = line.replace('goagent','lfengstudy')
        new_conf_file.write(line)
    new_conf_file.close()
    os.rename(self.goagent_conf, self.goagent_bk)
    os.rename(self.goagent_conf_new, self.goagent_conf)
    
  def _upload(self):
    cmd = 'cd ' +  self.goagent_server + ' && python uploader.zip'
    os.system(cmd)

if __name__ == "__main__":
  wall = goagent()
  wall.Start()
