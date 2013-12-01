import logging

def log1():
  logging.basicConfig(format='%(asctime)s   [%(levelname)s]:  %(message)s', filename='/tmp/test.log', level=logging.DEBUG)
  logging.debug('log_debug')
  logging.info('log_info')
  logging.warning('log_warning')
  logging.error('log_error')

def log2():
  logger = logging.getLogger(__name__)
  logger.setLevel(logging.DEBUG)

  # create a file handler
  handler = logging.FileHandler('/tmp/hello.log')
  handler.setLevel(logging.DEBUG)

  # create a logging format
  formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
  handler.setFormatter(formatter)

  # add the handlers to the logger
  logger.addHandler(handler)

  logger.info('Hello baby')

if __name__ == '__main__':
  log2()
