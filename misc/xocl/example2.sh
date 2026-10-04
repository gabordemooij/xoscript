gmake clean
USE_GTK=1 gmake 
xsltproc xslt/gtk.xsl example/example.html > /tmp/input_xocl.xml
./xocl -r default -g gtk -i /tmp/input_xocl.xml -o /tmp/output_xocl.txt
