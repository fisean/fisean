#!/bin/sh

MY_PATH=`dirname $0`

pkg install -y ccache fltk font-adobe-100dpi
cp ${MY_PATH}/.cshrc ~devel/.cshrc
chown devel:devel ~devel/.cshrc
