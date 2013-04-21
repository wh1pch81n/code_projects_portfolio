#!/bin/sh
cd ~/Dropbox/nand2tetris/tools
/usr/bin/java -classpath "${CLASSPATH}:bin/classes:bin/lib/Hack.jar:bin/lib/Compilers.jar" Hack.Compiler.JackCompiler $1
