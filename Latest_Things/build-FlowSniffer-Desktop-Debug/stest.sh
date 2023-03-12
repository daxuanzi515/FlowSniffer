# !/bin/bash
PID=$(pgrep -f Test)
echo "$PID"
kill -INT $PID

