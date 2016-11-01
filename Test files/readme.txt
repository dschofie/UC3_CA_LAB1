Arguments for each utility:


-u 0 -i ./imagen.img -o histogram.txt -t 25

-u 1 -i ./imagen.img -o maxmin.txt

-u 2 -i ./imagen.img -o mask_out.img -f mask.img
//maybe 90. Originally 45.
./ARCfmt -u 3 -i ./imagen.img -o rot_out.img -a -90

./ARCfmt -u 4 -i ./image.img -o circle_out.imf -r 16
