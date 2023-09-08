#!/bin/bash
# Download resources.zip unzip it into ./resources and delete the zip file.

GREEN="\e[0;32m"
YELLOW="\e[0;33m"
CYAN="\e[0;36m"
RESET="\e[0m"
FILEID="1soWV5bMXDHAR9yzlh_VhCKqDQjki0t37"
FILENAME="resources.zip"

printf "${YELLOW}\e[JDownloading resources.zip ...\n\e[F${RESET}"
curl -c ./cookie -s -L "https://drive.google.com/uc?export=download&id=${FILEID}" > /dev/null
curl -Lb ./cookie -s "https://drive.google.com/uc?export=download&confirm=`awk \
'/download/ {print $NF}' ./cookie`&id=${FILEID}" -o ${FILENAME}
rm cookie

printf "${YELLOW}\e[JExtracting resources.zip to resources ...\n\e[F${RESET}"
unzip -qq resources.zip
rm resources.zip

printf "${GREEN}\e[J[INFO] resources ready!\n${RESET}"
