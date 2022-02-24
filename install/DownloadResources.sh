
# Note: Numbers are 1024-byte units on Linux, and 512-byte units on macOS.
if [[ "$OSTYPE" == "linux-gnu"* ]] ; then
	units=512
	fileid="1J6ujchWjAcnpM-dIRYTxoltTOma715Hi"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    units=1024
	fileid="1J6ujchWjAcnpM-dIRYTxoltTOma715Hi"
elif [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "win32" ]]; then
    units=512
	fileid="1nbvBJ3ODNWr-jG7rfbAbiHkspc88MzMb"
else
    echo Error: Unsuported operating system.
	exit 1
fi

reqSpace=$((45 * 1000000 / $units))
availSpace=$(df "$HOME" | awk 'NR==2 { print $4 }')
if (( availSpace < reqSpace )); then
	echo "\033[1;31mNot enough Space:\033[0m $(($availSpace * $units / 1000000))/$(($reqSpace * $units / 1000000)) MB " >&2
	echo "After install sace required ~280MB"
	exit 1
fi
filename="resources.zip"
html=`curl -c ./cookie -s -L "https://drive.google.com/uc?export=download&id=${fileid}"`
curl -Lb ./cookie -s "https://drive.google.com/uc?export=download&`echo ${html}|grep -Po '(confirm=[a-zA-Z0-9\-_]+)'`&id=${fileid}" -o ${filename}
rm cookie
