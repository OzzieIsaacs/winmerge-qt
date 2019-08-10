#!/bin/sh

groff -t -e -mandoc -Tascii xdiff.3 | col -bx > xdiff.txt
groff -t -e -mandoc -Tps xdiff.3 | ps2pdf - xdiff.pdf
man2html < xdiff.3 | sed 's/<BODY>/<BODY text="#0000FF" bgcolor="#FFFFFF" style="font-family: monospace;">/i' > xdiff.html

