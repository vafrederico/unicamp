#!/bin/sh
echo "Compiling...."
hadoop com.sun.tools.javac.Main Friends*.java
echo "Jar'ing...."
jar cf FriendsJob.jar Friends*.class


