for i in 0 1 2 3 4 5 6 7 8 9
do
	var=`cat file`
	echo $var
	expr $var + 1 > file
done

