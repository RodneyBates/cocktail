lib=LIB
infile=
lalr_args=
use_bnf=false
bnf_args=
bnf_file=/tmp/lalr$$

while test $# != 0
do
  case $1 in
    -b)			use_bnf=true;;
    -c | -l | -m | -g)	lalr_args="$lalr_args $1"; bnf_args="$bnf_args $1";;
    -NoAction)		bnf_args="$bnf_args $1";;
    -* | [0-9]*)	lalr_args="$lalr_args $1";;
    *)			in_file="$in_file $1";;
  esac
  shift
done

trap "rm -f $bnf_file" 1 2 3 15

if $use_bnf
then
  $lib/lalr/bnf $in_file $bnf_args > $bnf_file
  status=$?
  if test $status = 0
  then
    $lib/lalr/lalr $bnf_file $lalr_args
    status=$?
  else
    cat $bnf_file
  fi
  rm $bnf_file
else
  $lib/lalr/lalr $in_file $lalr_args
  status=$?
fi
if test -w _Debug -a ! \( -s _Debug \)
then
  rm _Debug
fi
exit $status
