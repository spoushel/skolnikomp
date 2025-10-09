a="nazev.txt.agh.tt"
#echo ${a:0:1}
#echo ${a:: -3}
#awk -F. '{print $2}' <<< "$a"
#echo "$a" | awk -F. '{print $NF}'
echo "${a##*.}"
#echo "${a%%.*}"
#echo {a%.txt}
#echo "$a" | awk -F. '{print $1}'
#pwd
#pwd | awk -F/ '{print $1}'
# musi to byt bud nic nebo ~
#echo "${a%%.*}"