from bae.core.wsgi import WSGIApplication
import web

urls = (
    '/', 'index'
)

class index:
    def GET(self):
        return "Hello, world!"

app = web.application(urls, globals()).wsgifunc()
application = WSGIApplication(app)
