# Read from the file file.txt and output the tenth line to stdout.

function get_text
{
	let i=0
	while [ $i != 10 ]; do
	read line
	let i=$i+1
	done
	echo $line
}

get_text < file.txt
