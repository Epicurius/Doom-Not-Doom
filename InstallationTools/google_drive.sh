# Note: Numbers are 1024-byte units on Linux, and 512-byte units on macOS.
units=512
reqSpace=$((450 * 1000000 / $units))
availSpace=$(df "$HOME" | awk 'NR==2 { print $4 }')
if (( availSpace < reqSpace )); then
	echo "\033[1;31mNot enough Space:\033[0m $(($availSpace * $units / 1000000))/$(($reqSpace * $units / 1000000)) MB " >&2
	echo "After install sace required ~280MB"
	exit 1
fi
printf "\033[0;36m"
fileid="19_wBvvbEuSnkhDEvxxdylP1BjGMXhbFx"
filename="file.tar.gz"
curl -c ./cookie -s -L "https://drive.google.com/uc?export=download&id=${fileid}" > /dev/null
curl -Lb ./cookie -# "https://drive.google.com/uc?export=download&confirm=`awk '/download/ {print $NF}' ./cookie`&id=${fileid}" -o ${filename}
printf "\033[0m"
rm cookie
