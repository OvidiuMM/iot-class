#!/bin/bash
 
#vars***********
readonly path_to_main="/usr/local/TempHumProj/"
readonly main_name="tempAPP"
readonly log_file="app_log.txt"

#functions *************
function usage()
{
name=$0
echo -e "USAGE: \n 	$name <-s|-k|-r|-f]" 
echo -e "	-s start app program" 
echo -e "	-k kill app program" 
echo -e "	-r print log file content" 
echo -e "	-f start app program and write output
 to log file (in the same directory)" 
exit 1
}

function kill_main(){
result=$(ps -ef| grep -v grep | grep -i $main_name | head -n 1 | awk '{print $2}')
echo "killing process $result..."
if [[ -n $result ]]
then
 kill -9 $result
	echo "$main_name stoped..."

else
	echo "$main_name not found"
fi	
}

function start_main(){
check_conf
name=$1
if [[ -f ${name} ]] 
then
bash ${name}
echo "Starting $main_name app "
else
echo "no file named $name"
exit 1
fi
}

function log_file(){
check_conf
dt=$(date '+%d/%m/%Y %H:%M:%S');
echo ${dt} >>  ${path_to_main}${log_file}
echo "Logs will be stored in ${path_to_main}${log_file}"
bash ${path_to_main}$main_name  2>&1 | tee -a ${path_to_main}${log_file}
echo "Starting $main_name app "
}

function check_conf(){
if [[ ! -f ${path_to_main}$main_name ]] ; then
    echo -e "ERROR: Main app file $main_name not found in path ${path_to_main}!"
    usage	
fi

if [[ ! -f ${path_to_main}$log_file ]] ; then
    echo -e "Creating $log_file file in ${path_to_main}"
    touch ${path_to_main}${log_file}
fi
already_exists=$(ps -ef| grep -v grep | grep -i $main_name | head -n 1| awk '{print $2}')
if [[ -n $already_exists ]]
then
	echo "$main_name already running"
	exit 1
fi
}


#main thread ******
if [ $# -eq 0 ]
  then
    echo -e "No arguments supplied\n"
    usage
fi
while getopts ":skfr" opt; do
  case $opt in
      f)
	log_file ${path_to_main}$main_name
      ;;
    k)
	kill_main $main_name
      ;;
    s)
	start_main ${path_to_main}$main_name

      ;;
r)
if [[ ! -f ${path_to_main}$log_file ]] ; then

	cat ${path_to_main}${log_file}
else
echo "there is no log file"
fi
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      usage 
      ;;
    :)
      echo "Option -$OPTARG requires an argument." >&2
      usage
      ;;
  esac
done
