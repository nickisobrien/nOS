#!/bin/bash

#logging
datetime=$(date -u +%F_%H%M)
log_dir=${HOME}/logs/log_${datetime}

if [ ! -d ${HOME}/logs ]; then
  mkdir -p ${HOME}/logs
fi
mkdir -p ${log_dir}
echo "Logging to ${log_dir}"

function onexit {
	if [ $? -ne 0 ]; then
		echo "FAIL! Check log directory ${log_dir}"
	fi
}
trap onexit EXIT
