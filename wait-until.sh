# first argument should be a valid time e.g. 3:00 PM
sleep $(($(date -d "$1" '+%s') - $(date '+%s'))) 
