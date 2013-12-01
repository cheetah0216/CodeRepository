import logging
import logging.config

# load my module
import my_log

logging.basicConfig(format='%(asctime)s %(name)s  [%(levelname)s]:  %(message)s', filename='/tmp/test.log', level=logging.DEBUG)

my_log.foo()
bar = my_log.Bar()
bar.bar()
