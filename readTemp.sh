#!/bin/bash
while true; do
API_KEY='VWH1Y8NWJ9BCE0KG'
OUTPUT=$(sudo ./dht22)
HUMID=$(echo "$OUTPUT" | head -n 1 | tr -d '\n')
TEMP=$(echo "$OUTPUT" | tail -n 1 | tr -d '\n')
curl -k --data "api_key=$API_KEY&field1=$HUMID&field2=$TEMP" https://api.thingspeak.com/update
sleep 300
done
