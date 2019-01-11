set -e

g++ csg_img.cpp -o csg_img.out -std=c++0x > compile.log 2>&1

python orbit.py > orbit.data

mkdir -p imgs

idx=1
while read params
do
    imgname="${idx}.bmp"
    ./csg_img.out ./imgs/$imgname $params &
    idx=`expr $idx + 1`
done < ./orbit.data

