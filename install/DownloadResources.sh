# Note: Numbers are 1024-byte units on Linux, and 512-byte units on macOS.
units=512
reqSpace=$((450 * 1000000 / $units))
availSpace=$(df "$HOME" | awk 'NR==2 { print $4 }')
if (( availSpace < reqSpace )); then
	echo "\033[1;31mNot enough Space:\033[0m $(($availSpace * $units / 1000000))/$(($reqSpace * $units / 1000000)) MB " >&2
	echo "After install sace required ~280MB"
	exit 1
fi
fileid="1LAWX05hjoeKsoHuicL8OYY4B1hNEsF73"
filename="file.tar.gz"
curl -c ./cookie -s -L "https://drive.google.com/uc?export=download&id=${fileid}" > /dev/null
curl -Lb ./cookie -s "https://drive.google.com/uc?export=download&confirm=`awk '/download/ {print $NF}' ./cookie`&id=${fileid}" -o ${filename}
rm cookie

```
if [[ "$OSTYPE" == "darwin"* ]] || [[ "$OSTYPE" == "linux-gnu"* ]] ; then
	units=512
	reqSpace=$((450 * 1000000 / $units))
	availSpace=$(df "$HOME" | awk 'NR==2 { print $4 }')
	if (( availSpace < reqSpace )); then
		echo "\033[1;31mNot enough Space:\033[0m $(($availSpace * $units / 1000000))/$(($reqSpace * $units / 1000000)) MB " >&2
		echo "After install space required ~280MB"
		exit 1
	fi
	fileid="1LAWX05hjoeKsoHuicL8OYY4B1hNEsF73"
	filename="resources.zip"
	curl -c ./cookie -s -L "https://drive.google.com/uc?export=download&id=${fileid}" > /dev/null
	curl -Lb ./cookie -s "https://drive.google.com/uc?export=download&confirm=`awk '/download/ {print $NF}' ./cookie`&id=${fileid}" -o ${filename}
	rm cookie
	tar -xf resources.zip
	rm -rf resources.zip
	mkdir ./libs/SDL_MAC
	mv *.frameworks ./libs/SDL_MAC

elif [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "win32" ]]; then
	units=512
	reqSpace=$((450 * 1000000 / $units))
	availSpace=$(df "$HOME" | awk 'NR==2 { print $4 }')
	if (( availSpace < reqSpace )); then
		echo "\033[1;31mNot enough Space:\033[0m $(($availSpace * $units / 1000000))/$(($reqSpace * $units / 1000000)) MB " >&2
		echo "After install space required ~280MB"
		exit 1
	fi
	fileid="1LAWX05hjoeKsoHuicL8OYY4B1hNEsF73"
	filename="resources.zip"
	curl -c ./cookie -s -L "https://drive.google.com/uc?export=download&id=${fileid}" > /dev/null
	curl -Lb ./cookie -s "https://drive.google.com/uc?export=download&confirm=`awk '/download/ {print $NF}' ./cookie`&id=${fileid}" -o ${filename}
	rm cookie
	tar -xf resources.zip
	rm -rf resources.zip
	mkdir ./libs/SDL_WIN
	mv *.lld ./libs/SDL_WIN
else
	echo "Operating system not detected, dont know what libraries to download!"
fi
```