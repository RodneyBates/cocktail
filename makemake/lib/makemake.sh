 # makemake: makefile generator
: set -x
LIB=.
text="usage: makemake [directories]"
awk=$LIB/makemake/makemake.awk

trap 'exit 1' 1 2 3 15

if test $# -eq 1
then
   case $1 in
	 -*) echo "$text"; exit 1;;
	  *) ;;
   esac
fi

if test $# -eq 0
then dirs=.
else dirs=$*
fi

for dir in $dirs
do
   for file in `ls $dir/*.md`
   do
      echo CONFIRM `basename $file .md`
   done
   for file in `ls $dir/*.m[di]`
   do
      $LIB/makemake/GetImports -l$LIB/makemake < $file || echo "makemake: error in module $file" 1>&2
   done
done |

awk -f $awk
