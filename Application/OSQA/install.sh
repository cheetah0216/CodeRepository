#!/bin/bash
OSQAHome=$1
WSGIScriptDir=$OSQAHome/osqa-server/osqa.wsgi
OSQAApacheConf=/etc/apache2/sites-available/osqa
source  /etc/apache2/envvars
#################### Get OSQA source code ############################
#svn co http://svn.osqa.net/svnroot/osqa/trunk/ $OSQAHome/osqa-server


#################### Apache Web Server ###############################
#Install Apache
#sudo apt-get -y install apache2 libapache2-mod-wsgi

#Update the OSQA WSGI Script
cat <<WSGI-SCRIPT >$WSGIScriptDir
import os
import sys
sys.path.append('$OSQAHome')
sys.path.append('$OSQAHome/osqa-server')
# The first part of this module name should be identical to the directory name
# of the OSQA source.  For instance, if the full path to OSQA is
# /home/osqa/osqa-server, then the DJANGO_SETTINGS_MODULE should have a value
# of 'osqa-server.settings'.
os.environ['DJANGO_SETTINGS_MODULE'] = 'osqa-server.settings'
import django.core.handlers.wsgi
application = django.core.handlers.wsgi.WSGIHandler()
WSGI-SCRIPT

#Remove the Default Apache Configurations
sudo rm /etc/apache2/sites-available/default\
    /etc/apache2/sites-available/default-ssl\
    /etc/apache2/sites-enabled/000-default

#Add the OSQA Configuration to Apache
cat <<OSQA-Apache-Conf >$OSQAApacheConf
# Must be readable and writable by apache
WSGISocketPrefix ${APACHE_RUN_DIR}

#NOTE: all urs below will need to be adjusted if
#settings.FORUM_SCRIPT_ALIAS !='' (e.g. = 'forum/')
#this allows "rooting" forum at [http://example.com/forum], if you like
<VirtualHost *:80>
	ServerAdmin forum@cienet.com.cn
	DocumentRoot $OSQAHome/osqa-server
	ServerName cienet.com.cn

	#run mod_wsgi process for django in daemon mode
	#this allows avoiding confused timezone settings when
	#another application runs in the same virtual host
	WSGIDaemonProcess OSQA
	WSGIProcessGroup OSQA

	#force all content to be served as static files
	#otherwise django will be crunching images through itself wasting time
	Alias /m/ "$OSQAHome/osqa-server/forum/skins/"
        <Directory "$OSQAHome/osqa-server/forum/skins">
                Order allow,deny
                Allow from all
        </Directory>
	Alias /upfiles/ "$OSQAHome/osqa-server/forum/upfiles/"
	<Directory "$OSQAHome/osqa-server/forum/upfiles">
		Order deny,allow
		Allow from all
	</Directory>

	#this is your wsgi script described in the prev section
	WSGIScriptAlias / $OSQAHome/osqa-server/osqa.wsgi

	CustomLog ${APACHE_LOG_DIR}/osqa.access.log common
	ErrorLog ${APACHE_LOG_DIR}/osqa.error.log
</VirtualHost>
OSQA-Apache-Conf

#Link to the OSQA config in the sites-enabled directory
sudo ln -s /etc/apache2/sites-available/osqa /etc/apache2/sites-enabled/osqa


#################################### MySQL Database Server ########################################
#Installing MySQL
#sudo apt-get -y install mysql-server mysql-client
#sudo mysql -u root -p

#CREATE USER 'osqa'@'localhost' IDENTIFIED BY 'your_osqa_password';
#CREATE DATABASE osqa DEFAULT CHARACTER SET UTF8 COLLATE utf8_general_ci;
#GRANT ALL ON osqa.* to 'osqa'@'localhost';

################################### Python ##################################
#sudo apt-get -y install python

#Python Setup Tools
#sudo apt-get -y install python-setuptools

#sudo apt-get -y install python-mysqldb
#sudo easy_install South django django-debug-toolbar markdown \
#    html5lib python-openid

################################ Configure OSQA Settings #############################
cp $OSQAHome/osqa-server/settings_local.py.dist $OSQAHome//osqa-server/settings_local.py

