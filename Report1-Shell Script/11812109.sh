#! /bin/bash
set -f # Close wildcard
if [ ! -d "$1" ]
    then
        echo Test folder path is incorrect, exit script
        exit 0
    fi
ori_path=`pwd`
out_file=`basename "$2"`
out_dir=`dirname "$2"`
if [ ! -d "${out_dir}" ]
    then
        echo The file output path is incorrect, exit the script
        exit 0
    fi
cd "${out_dir}"
out_path="`pwd`/${out_file}"
cd "${ori_path}"
cd "$1"
t=0
j=0
k=0
arr[${k}]="`pwd`"
k=$(($k+1))
> ${out_path}
while [ $j -lt $k ]
do
    # header
    bname=`basename "${arr[$j]}"`
    echo "[${bname}]" >> ${out_path}
#    str="${arr[$j]}"
#    cov_path=""
#
#    for i in `seq ${#str}`
#    do
#        if [ "${str:$i-1:1}" == "*" ]
#        then
#            cov_path=${cov_path}\\${str:$i-1:1}
#        else
#            cov_path=${cov_path}${str:$i-1:1}
#        fi
#    done
    cov_path="${arr[$j]}"
    
    # detail
    for var in `ls "${cov_path}" | tr " " "/"`
    do
        e=`tr "/" " " <<< ${var}`
        dir_or_file="${arr[$j]}"/"$e"
        echo "$dir_or_file" >> ${out_path}
        
        if [ -d "$dir_or_file" ]
        then
            arr[${k}]="$dir_or_file"
            k=$(($k+1))
        fi
        t=$(($t+1))
    done
    echo -e >> ${out_path}
    j=$(($j+1))
done

j=$(($j-1))
echo [Directories Count]:${j} >> ${out_path}
echo [Files Count]:$(($t-$j)) >> ${out_path}
cd "${ori_path}"
set +f # Restore wildcard

# dirname basename
#getDirName=`pwd |awk -F '/' '{print $NF}'`
#echo "[${getDirName:-"/"}]"
