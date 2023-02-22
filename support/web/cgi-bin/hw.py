#!/usr/bin/python3
import sys
import time
import traceback
import subprocess
import re
import json

print("Content-type: text/plain; charset=iso-8859-1\n")

## Make all, what You want, remember, that You not in global environment, and not as root

# Get IPs
cmd = "hostname -I"
IP = subprocess.check_output(cmd, shell = True ).decode('utf-8').rstrip()
ipList = re.findall("\d+\.\d+\.\d+\.\d+", IP)

# Get processor usage
cmd = "top -bn1 | grep load | awk '{printf \"%.2f\", $(NF-2)}'"
CPU_load = subprocess.check_output(cmd, shell = True ).decode('utf-8').rstrip()

# Get RAM usage
cmd = "free -m | awk 'NR==2{printf \"%.2f%%\", $3*100/$2 }'"
MemUsage = subprocess.check_output(cmd, shell = True ).decode('utf-8').rstrip()

# Get SD card usage
cmd = "df -h | awk '$NF==\"/\"{printf \"%s\", $5}'"
Disk = subprocess.check_output(cmd, shell = True ).decode('utf-8').rstrip()

ret = []
ret.append({"label": "HDD", "value": Disk});
ret.append({"label": "CPU load", "value": CPU_load});
ret.append({"label": "RAM load", "value": MemUsage});
ret.append({"label": "IP(-s)", "value": IP});
print(json.dumps(ret))

