make clean
cp -R ~/cursus/cub3d/* ~/cursus/cub
rm -rf ~/cursus/cub/a.out.dSYM ~/cursus/cub/a.out
cd ../cub
git add .
git commit -m "change dir x/y to plane x/y in move forw/back"
git push origin main
cd ../cub3d
