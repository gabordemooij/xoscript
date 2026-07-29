gmake clean
gmake USE_GTK=1
xsltproc xslt/gtk.xsl example/example.html

xsltproc xslt/gtk.xsl example/example.html | ./xocl
