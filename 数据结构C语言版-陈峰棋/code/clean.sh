#!/bin/bash

# delete file: *.user
#find . -name "*.user" -delete
#find . -name "*.user" -exec rm {} \;
echo "delete files: *.user"
find . -name "*.user" | xargs rm -f

# delete folder: Debug
#find . -type d -name "Debug" -exec rm -rf {} \;
echo "delete folder: Debug"
find . -type d -name "Debug" | xargs rm -rf
find . -type d -name "debug" | xargs rm -rf
