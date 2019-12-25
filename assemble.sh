#!/bin/bash
#asembliranje .asm fajla upotrebom z80 asemblera

file_in=$1
file_out_main=${file_in::-4}
ekstenzija=".bin"
file_out="${file_out_main}${ekstenzija}"
cd /home/dianas/Downloads/z80-asm-current/z80-asm-2.4.1
errors=`z80-asm ${file_in} ${file_out} 2>&1`
if [ -z "$errors" ]
then
    echo "File is successfully assembled"
else
    echo "$errors"
fi
