#!/bin/bash

#temporary dev install
g++ -pthread src/server.c src/handler.c src/httptime.c -o serverlight
