if [ ! -e $1 ]; then
	echo "Inputfile doesnt exist. Exitting...."
	exit 1
fi
if [ ! -e $2 ]; then
	touch $2
fi
if [ -e "hillclimb" ]; then
	./hillclimb $1 $2
else
	echo "First run compile.sh to compile the code"
fi 