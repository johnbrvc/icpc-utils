#!/usr/bin/python3
import subprocess
import HtmlFunctions

HOSTS_FILE="/etc/hosts"
JUDGE_PREFIX="pc2-aj"
JUDGE_STYLES="/css/judgestyles.css"


HtmlFunctions.Preamble(None)
HtmlFunctions.Styles(JUDGE_STYLES)
HtmlFunctions.StartHTMLDoc()

p = subprocess.Popen("egrep '^[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}[[:space:]]" + JUDGE_PREFIX + "[0-9][0-9]*' " + HOSTS_FILE,
        shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
for line in p.stdout.readlines() :
    sval = line.decode().split();
    if len(sval) == 2 :
        print(sval[1])
retval = p.wait()
print(f"Return code {retval}")

HtmlFunctions.Trailer()
