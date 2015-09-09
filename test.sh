#!/bin/bash
sudo ./rfread &
curl --silent http://metaphorpsum.com/sentences/1 | sudo ./rfwrite
sudo kill $!
