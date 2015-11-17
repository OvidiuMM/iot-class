#!/bin/bash
 
readonly path_to_main="./"
readonly main_name="main"
readonly log_file="app_log.txt"

function usage(){
name=$0
echo -e "USAGE: \n 	$name <-s|-k>[-f]" 
echo -e "	-s start app program" 
echo -e "	-k kill app program" 
echo -e "	-f start app program and write output to log file (in the same directory)" 
exit 1
}

function kill_main(){
kill -9 `ps -ef|grep -v grep |grep $1| awk '{print $2}'`
}

function start_main(){
check_conf
name=$1
${name}
}

function log_file(){
check_conf
name=$1
dt=$(date '+%d/%m/%Y %H:%M:%S');
echo ${dt} >>  ${path_to_main}${log_file}
./${name} 2>&1 | tee -a ${path_to_main}${log_file}

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
}



if [ $# -eq 0 ]
  then
    echo -e "No arguments supplied\n"
    usage

fi
while getopts ":skf" opt; do
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
