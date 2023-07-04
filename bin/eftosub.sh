#!/bin/bash
( echo "["
  sed -n -e '/"submissions"/{s/^.*"data"://;s/}]},"time.*/}]},/;p}' | sed -e '$ s/,$//'
  echo "]"
) | json_pp
