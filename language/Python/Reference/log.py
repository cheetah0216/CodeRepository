import logging

logging.basicConfig(format='%(asctime)s   [%(levelname)s]:  %(message)s', filename='/tmp/test.log', level=logging.DEBUG)
logging.debug('log_debug')
logging.info('log_info')
logging.warning('log_warning')
logging.error('log_error')
