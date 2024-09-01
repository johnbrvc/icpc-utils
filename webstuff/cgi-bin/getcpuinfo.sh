#!/bin/bash
echo "Content-type: application/json"
echo "Access-Control-Allow-Origin: *"
echo ""
echo "{"
echo -n '"cpuinfo": '; env --default-signal=14 mpstat -P ALL -o JSON 1 1
echo ","
echo -n '"judgments": '; ls /home/icpc/html/cache | wc -l
echo ","
echo -n '"diskused": ';df / --output=pcent | sed -e 1d -e 's/  *//g' -e 's/%//g'
echo "}"
exit 0
