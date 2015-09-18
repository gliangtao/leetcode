# Read from the file file.txt and output all valid phone numbers to stdout.
#!/bin/bash

function filterPhoneNum
{
	while [ true ]; do
		read line
		if [[ "$line" =~ ^([0-9]{3}-|\([0-9]{3}\) )[0-9]{3}-[0-9]{4}$ ]]; then
			echo $line
		elif [ -z "$line" ]; then
			return
		fi
	done
}

filterPhoneNum <file.txt
