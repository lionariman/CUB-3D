make clean
cp -R ~/cursus/cub3d/* ~/cursus/cub
cd ../cub
git add .
git commit -m "new changes"
git push origin main
cd ../cub3d
rm -rf ~/cursus/cub/a.out.dSYM ~/cursus/cub/a.out
