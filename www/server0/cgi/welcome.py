#!/usr/bin/python

import cgi
import html
import cgitb; cgitb.enable()  # for troubleshooting

# print "HTTP/1.1 200 OK"
# print "Content-type: text/html"
# print

print("""
<html>

<head><title>Sample CGI Script</title></head>

<body>

  <h3> Sample CGI Script </h3>
""")

form = cgi.FieldStorage()
message = form.getvalue("message", "(no message)")

print("""

  <p>Previous message: %s</p>

  <p>form

  <form method="post" action="welcome.py">
    <p>message: <input type="text" name="message"/></p>
  </form>

</body>

</html>
""" % html.escape(message))