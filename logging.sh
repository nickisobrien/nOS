#!/bin/bash

#logging
datetime=$(date -u +%F_%H%M)
log_dir=${HOME}/logs/log_${datetime}

if [ ! -d ${HOME}/logs ]; then
  mkdir -p ${HOME}/logs
fi
mkdir -p ${log_dir}
echo "Logging to ${log_dir}"
