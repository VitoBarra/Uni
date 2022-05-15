 if [ $# -ne 8 ] ; then 
 echo "To few argument, shuld be -d [directory] -s [number] -f [number] - n [number]"
  exit 1 
 fi

./CreateFile.sh
# to create file with size in megabite use
# truncate -s 5M ./dir/file5M 
 while getopts d:s:f:n: flag; do
  case "${flag}" in
    d) dir=${OPTARG} ;;
    s) size=$((${OPTARG}*1024*1024));;
    f) warning_factor=${OPTARG} ;;
    n) maxnum=${OPTARG} ;; 
  esac
done

function GetOrderedFileName () 
{
  doneSortedFileDir=()
  readarray -t SortedFile < <( find dir/ -type f -printf '%A@ %s %p\n'| sort)
  for i in "${SortedFile[@]}"; do
    arr=($i)
    Line=${arr[2]}
    doneSortedFileDir+=($Line)
  done 
  unset i
}

function GetCurrentFreeSpace () 
{
  readarray -t SortedFile < <( find dir/ -type f -printf '%A@ %s %p\n'| sort)
  local i
  TotalUsage=0
  for i in "${SortedFile[@]}"; do
    arr=($i)
    ((TotalUsage+=${arr[1]}))
  done 
  unset i


  FreeSpace=$(( $size - $TotalUsage ))
}


function WhileDebug()
{
  echo "------------------------------------------------------------"
  echo "FreeSpace:$(( $size - $TotalUsage )) =  $size - ${TotalUsage}"
  echo "--------------------------- ${j} ------------------------------"
  echo "Warning: ${Warning}=${size}*${warning_factor}"
  echo "${FreeSpace} < ${Warning}"
  echo "File To Remove: ${doneSortedFileDir[j]}"
}


GetOrderedFileName




j=0
while : ; do
  GetCurrentFreeSpace
  Warning=$(bc <<< "${size}*${warning_factor}")
  # WhileDebug
  [ "$(bc <<< "${FreeSpace} < ${Warning} && (${size} != 0 || ${j} < ${size})")" == "1" ] || break
  rm ${doneSortedFileDir[j]}
  ((j+=1))
  # ./Wait.sh
done

GetOrderedFileName

#./compito4.sh -d ./dir -s 14 -f 0.1 -n 0
#./compito4.sh -d ./dir -s 14 -f 0.35 -n 0