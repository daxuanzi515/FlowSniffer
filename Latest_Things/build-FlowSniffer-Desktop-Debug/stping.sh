# !/bin/bash
PID=$(pgrep -f Ping)
echo "$PID"
kill -INT $PID

