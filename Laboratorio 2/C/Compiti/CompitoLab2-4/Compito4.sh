#!/bin/bash 

 
 if [ $# -ne 8 ] ; then 
 echo "To few argument, should be -d [directory] -s [number] -f [number] - n [number]"
  exit 1 
 fi


 while getopts d:s:f:n: flag; do
  case "${flag}" in
    d) dir=${OPTARG} ;;
    s) size=$((${OPTARG}*1024*1024));;
    f) warning_factor=${OPTARG} ;;
    n) maxnum=${OPTARG} ;; 
    *) echo "should be -d [directory] -s [number] -f [number] - n [number]"
  esac
done


function GetOrderedFileName 
{
  doneSortedFileDir=()
  readarray -t SortedFile < <( find ${dir}/ -type f -printf '%A@ %s %p\n'| sort)
  local i
  for i in "${SortedFile[@]}"; do
    arr=($i)
    Line=${arr[2]}
    doneSortedFileDir+=($Line)
  done 
  unset i
}

function GetCurrentFreeSpace
{
  readarray -t SortedFile < <( find ${dir}/ -type f -printf '%A@ %s %p\n'| sort)
  local i
  TotalUsage=0
  for i in "${SortedFile[@]}"; do
    arr=($i)
    ((TotalUsage+=${arr[1]}))
  done 
  unset i
  FreeSpace=$(( $size - $TotalUsage ))
}

GetOrderedFileName


Warning=$(bc <<< "${size}*${warning_factor}")
echo "------------------------------------------------------------"
echo "Warning: ${Warning} = ${size}*${warning_factor}"
GetCurrentFreeSpace
echo "FreeSpace:${FreeSpace} = ${size} - ${TotalUsage}"

j=0
while [ "$(bc <<< "${FreeSpace} < ${Warning} && (${maxnum} == 0 || ${j} < ${maxnum})")" -eq "1" ]; do


  echo "--------------------------- ${j} ------------------------------"
  rm ${doneSortedFileDir[j]}
  echo "removed: ${doneSortedFileDir[j]}"
  GetCurrentFreeSpace
  echo "FreeSpace:${FreeSpace} = ${size} - ${TotalUsage}"

  ((j+=1))
done

echo ""
echo "File Rimossi ${j}"