make clean
cp -R ~/cursus/cub3d/* ~/cursus/cub
rm -rf ~/cursus/cub/a.out.dSYM ~/cursus/cub/a.out
cd ../cub
git add .
git commit -m "a little bit more shorter"
git push origin main
cd ../cub3d
