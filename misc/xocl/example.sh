gmake clean
USE_GTK=1 gmake 

xsltproc xslt/gtk.xsl example/example.html

xsltproc xslt/gtk.xsl example/example.html | ./xocl
